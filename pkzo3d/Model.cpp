// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Model.h"

#include <map>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <pkzo/stdng.h>
#include <pkzo/debug.h>

#include "Group.h"
#include "MeshGeometry.h"

namespace pkzo3d
{
    using pkzo::trace;
    using pkzo::check;
    using pkzo::MeshData;

    std::shared_ptr<Model> Model::load(const std::filesystem::path& file)
    {
        static std::map<std::filesystem::path, std::weak_ptr<Model>> cache;

        auto i = cache.find(file);
        if (i != end(cache))
        {
            auto cached_model = i->second.lock();
            if (cached_model)
            {
                return cached_model;
            }
        }

        auto model = std::make_shared<Model>(file);
        cache.insert_or_assign(file, model);
        return model;
    }

    glm::vec3 to_glm(const aiVector3D& v)
    {
        return {v.x, v.y, v.z};
    }

    glm::mat4 to_glm(const aiMatrix4x4& from)
    {
        glm::mat4 to;
        to[0][0] = from.a1; to[0][1] = from.b1;  to[0][2] = from.c1; to[0][3] = from.d1;
        to[1][0] = from.a2; to[1][1] = from.b2;  to[1][2] = from.c2; to[1][3] = from.d2;
        to[2][0] = from.a3; to[2][1] = from.b3;  to[2][2] = from.c3; to[2][3] = from.d3;
        to[3][0] = from.a4; to[3][1] = from.b4;  to[3][2] = from.c4; to[3][3] = from.d4;
        return to;
    }

    glm::uvec3 to_glm(const aiFace& f)
    {
        check(f.mNumIndices == 3); // faces should have been triangulated.
        return {f.mIndices[0], f.mIndices[1], f.mIndices[2]};
    }

    void assimp_log(const char* msg, char* dt)
    {
        trace(msg);
    }

    const auto assimp_log_stream = aiLogStream{
        .callback = assimp_log,
        .user     = nullptr
    };

    class AssimpInitializer
    {
    public:
        AssimpInitializer()
        {
            aiAttachLogStream(&assimp_log_stream);
        }

        ~AssimpInitializer()
        {
            aiDetachAllLogStreams();
        }

    } assimp_init;

    pkzo::Format assimp_get_format(const std::string_view hint)
    {
        using stdng::hash;
        using enum pkzo::Format;
        switch (hash(hint))
        {
            case hash("jpg"):
                return JPEG;
            case hash("png"):
                return PNG;
            case hash("gif"):
                return GIF;
            case hash("tiff"):
                return TIFF;
            case hash("webp"):
                return WEBP;
            default:
                throw std::runtime_error(tfm::format("Assimp: Unsuported Format: %s", hint));
        }
    }

    pkzo::ColorMode assimp_get_color_mode(const char* hint)
    {
        using stdng::hash;
        using enum pkzo::ColorMode;
        switch (hash(hint))
        {
            case hash("rgba8888"):
                return RGBA;
            // TODO
            //case hash("argb8888"):
            //    return ColorMode::ARGB;
            //case hash("rgba5650"):
            //    return ColorMode::RGB565;
            //case hash("rgba0010"):
            //    return ColorMode::R1; // yes it's blue... but who cares it's mono
            default:
                throw std::runtime_error(tfm::format("Assimp: Unsuported Pixel Format: %s", hint));
        }
    }

    std::shared_ptr<Texture> assimp_load_texture(const aiTexture* texture)
    {
        if (texture->mHeight == 0) // is compressed
        {

            return Texture::load_memory({
                .format = assimp_get_format(texture->achFormatHint),
                .size   = texture->mWidth,
                .memory = reinterpret_cast<const void*>(texture->pcData),

            });
        }
        else
        {
            return Texture::create({
                .size       = {texture->mWidth, texture->mHeight},
                .data_type  = pkzo::DataType::UNSIGNED_BYTE,
                .color_mode = assimp_get_color_mode(texture->achFormatHint),
                .memory     = {reinterpret_cast<const void*>(texture->pcData)},
            });
        }
    }

    std::string get_material_image_path(const aiMaterial* material, aiTextureType type)
    {
        auto path = aiString{};
        auto result = material->GetTexture(type, 0, &path);
        return result == AI_SUCCESS ? std::string(path.C_Str()) : std::string{};
    }

    std::optional<std::shared_ptr<Texture>> assimp_load_texture(const aiMaterial* material, const std::filesystem::path& base, aiTextureType type, const std::vector<std::shared_ptr<Texture>>& textures)
    {
        auto path = get_material_image_path(material, type);
        if (path.empty())
        {
            return std::nullopt;
        }

        if (path[0] == '*')
        {
            auto i = std::stoi(path.substr(1));
            return textures.at(i);
        }
        else
        {
            return Texture::load_file({
                .file = base / path
            });
        }
    }

    std::optional<float> assimp_material_float(const aiMaterial* material, const char* pKey,unsigned int type, unsigned int idx)
    {
        ai_real factor;
        auto r = material->Get(pKey, type, idx, factor);
        if (r == aiReturn_SUCCESS)
        {
            return factor;
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<glm::vec3> assimp_material_color(const aiMaterial* material, const char* pKey,unsigned int type, unsigned int idx)
    {
        aiColor3D color;
        auto r = material->Get(pKey, type, idx, color);
        if (r == aiReturn_SUCCESS)
        {
            return glm::vec3{color.r, color.g, color.b};
        }
        else
        {
            return std::nullopt;
        }
    }

    std::shared_ptr<Material> assimp_load_material(const aiMaterial* material, const std::filesystem::path& base, const std::vector<std::shared_ptr<Texture>>& textures)
    {
        auto props = Material::Props{};

        props.base_color_factor      = assimp_material_color(material, AI_MATKEY_BASE_COLOR).value_or(props.base_color_factor);
        props.base_color_map         = assimp_load_texture(material, base, aiTextureType_BASE_COLOR, textures).value_or(props.base_color_map);
        props.roughness_factor       = assimp_material_float(material, AI_MATKEY_ROUGHNESS_FACTOR).value_or(props.roughness_factor);
        props.metallic_factor        = assimp_material_float(material, AI_MATKEY_METALLIC_FACTOR).value_or(props.metallic_factor);
        props.metallic_roughness_map = assimp_load_texture(material, base, aiTextureType_DIFFUSE_ROUGHNESS, textures).value_or(props.metallic_roughness_map);
        props.normal_map             = assimp_load_texture(material, base, aiTextureType_NORMALS, textures).value_or(props.normal_map);
        props.emissive_factor        = assimp_material_color(material, AI_MATKEY_COLOR_EMISSIVE).value_or(props.emissive_factor);
        props.emissive_map           = assimp_load_texture(material, base, aiTextureType_EMISSIVE, textures).value_or(props.emissive_map);

        return Material::create(props);
    }

    std::shared_ptr<Mesh> assimp_load_mesh(aiMesh* mesh)
    {
        static_assert(sizeof(glm::vec3) == sizeof(aiVector3D));
        static_assert(alignof(glm::vec3) == alignof(aiVector3D));

        // Double check that assimp did it's job.
        check(mesh->mVertices);
        check(mesh->mNormals);
        check(mesh->mTangents);
        check(mesh->mTextureCoords[0]);
        check(mesh->mNumUVComponents[0] >= 1);

        auto init = MeshData{};

        init.vertexes.resize(mesh->mNumVertices);
        init.normals.resize(mesh->mNumVertices);
        init.tangents.resize(mesh->mNumVertices);
        init.texcoords.resize(mesh->mNumVertices);
        init.faces.resize(mesh->mNumFaces);

        std::transform(mesh->mVertices, mesh->mVertices + mesh->mNumVertices, begin(init.vertexes), [] (const auto& v) { return to_glm(v); } );
        std::transform(mesh->mNormals,  mesh->mNormals  + mesh->mNumVertices, begin(init.normals),  [] (const auto& v) { return to_glm(v); } );
        std::transform(mesh->mTangents, mesh->mTangents + mesh->mNumVertices, begin(init.tangents), [] (const auto& v) { return to_glm(v); } );

        std::transform(mesh->mTextureCoords[0], mesh->mTextureCoords[0] + mesh->mNumVertices, begin(init.texcoords), [] (const auto& texcoord) {
            return glm::vec2(texcoord.x, texcoord.y);
        });

        std::transform(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, begin(init.faces), [] (const auto& face) {
            check(face.mNumIndices == 3);
            return glm::uvec3(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
        });

        return Mesh::create(std::move(init));
    }

    std::unique_ptr<Model::Node> assimp_load_node(aiNode* ainode,
                                                  const std::vector<std::shared_ptr<Material>>& materials,
                                                  const std::vector<unsigned int>& material_indexes,
                                                  const std::vector<std::shared_ptr<Mesh>>& meshes)
    {
        auto node = std::make_unique<Model::Node>();

        // Collapse mesh node into this.
        if (ainode->mNumMeshes == 1 && ainode->mNumChildren == 0)
        {
            node->transform = to_glm(ainode->mTransformation);
            node->mesh      = meshes.at(ainode->mMeshes[0]);
            node->material  = materials.at(material_indexes.at(ainode->mMeshes[0]));
        }
        else
        {
            for (auto i = 0u; i < ainode->mNumMeshes; i++)
            {
                auto child = std::make_unique<Model::Node>();
                child->transform = to_glm(ainode->mTransformation);
                child->mesh      = meshes.at(ainode->mMeshes[i]);
                child->material  = materials.at(material_indexes.at(ainode->mMeshes[i]));
                node->children.push_back(std::move(child));
            }
        }

        for (auto i = 0u; i < ainode->mNumChildren; i++)
        {
            auto child = assimp_load_node(ainode->mChildren[i], materials, material_indexes, meshes);
            node->children.push_back(std::move(child));
        }

        return node;
    }

    Model::Model(const std::filesystem::path& file)
    {
        auto scene = aiImportFile(file.string().data(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (!scene)
        {
            throw std::runtime_error(tfm::format("Failed to load %s: %s", file, aiGetErrorString()));
        }
        auto scene_cleanup = stdng::scope_exit([&] () { aiReleaseImport(scene); });

        auto base = std::filesystem::canonical(file.parent_path());

        auto textures = std::vector<std::shared_ptr<Texture>>{};
        textures.reserve(scene->mNumTextures);
        for (auto i = 0u; i < scene->mNumTextures; i++)
        {
            textures.push_back(assimp_load_texture(scene->mTextures[i]));
        }

        auto materials = std::vector<std::shared_ptr<Material>>{};
        materials.reserve(scene->mNumMaterials);
        for (auto i = 0u; i < scene->mNumMaterials; i++)
        {
            materials.push_back(assimp_load_material(scene->mMaterials[i], base, textures));
        }

        auto meshes           = std::vector<std::shared_ptr<Mesh>>();
        auto material_indexes = std::vector<unsigned int>();
        meshes.reserve(scene->mNumMeshes);
        material_indexes.reserve(scene->mNumMeshes);
        for (auto i = 0u; i < scene->mNumMeshes; i++)
        {
            meshes.push_back(assimp_load_mesh(scene->mMeshes[i]));
            material_indexes.push_back(scene->mMeshes[i]->mMaterialIndex);
        }

        root_node = assimp_load_node(scene->mRootNode, materials, material_indexes, meshes);
    }

    Model::~Model() = default;

    void instantiate_group(Group& group, const Model::Node& node, bool collidable)
    {
        // A node has either a mesh & material or children, but not both.
        // Here we only handle group nodes as input.

        check(!node.children.empty());
        check(node.mesh == nullptr);
        check(node.material == nullptr);

        for (const auto& child : node.children)
        {
            if (!child->children.empty())
            {
                auto child_group = group.add<Group>({
                    .transform = child->transform
                });
                instantiate_group(*child_group, *child, collidable);
            }
            else
            {
                check(child->mesh);
                check(child->material);
                group.add<MeshGeometry>({
                    .transform  = child->transform,
                    .collidable = collidable,
                    .mesh       = child->mesh,
                    .material   = child->material
                });
            }
        }
    }

    void Model::instantiate(Group& group, bool collidable) const
    {
        if (!root_node->children.empty())
        {
            instantiate_group(group, *root_node, collidable);
        }
        else
        {
            check(root_node->mesh);
            check(root_node->material);
            group.add<MeshGeometry>({
                .transform  = root_node->transform,
                .collidable = collidable,
                .mesh       = root_node->mesh,
                .material   = root_node->material
            });
        }
    }
}
