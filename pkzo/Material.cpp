// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Material.h"

#include <pugixml.hpp>

#include "dbg.h"
#include "compose.h"
#include "stdex.h"
#include "Shader.h"
#include "Texture.h"

namespace pkzo
{
    Material::Material() = default;

    Material::Material(const fs::path& file)
    {
        load(file);
    }

    Material::~Material() = default;

    bool Material::has_uniform(const std::string& id) const
    {
        return uniforms.find(id) != uniforms.end();
    }

    const UniformValue& Material::get_uniform(const std::string& id) const
    {
        auto i = uniforms.find(id);
        if (i == uniforms.end())
        {
            PKZO_THROW(std::runtime_error, "Unknown uniform " + id);
        }
        return i->second;
    }

    void Material::set_uniform(const std::string& id, const UniformValue& value)
    {
        uniforms[id] = value;
    }

    bool Material::has_texture(const std::string& id) const
    {
        return textures.find(id) != textures.end();
    }

    const std::shared_ptr<Texture>& Material::get_texture(const std::string& id) const
    {
        auto i = textures.find(id);
        if (i == textures.end())
        {
            PKZO_THROW(std::runtime_error, "Unknown texture " + id);
        }
        return i->second;
    }

    void Material::set_texture(const std::string& id, const std::shared_ptr<Texture>& value)
    {
        textures[id] = value;
    }

    const std::shared_ptr<Shader>& Material::get_shader() const
    {
        return shader;
    }

    void Material::set_shader(const std::shared_ptr<Shader>& value)
    {
        shader = value;
    }

    void Material::swap(Material& other) noexcept
    {
        using std::swap;
        std::swap(uniforms, other.uniforms);
        std::swap(textures, other.textures);
        std::swap(shader, other.shader);
    }

    void Material::bind(Shader& shader)
    {
        for (auto& [id, value] : uniforms)
        {
            shader.set_uniform(id, value);
        }

        for (auto& [id, texture] : textures)
        {
            shader.set_texture(id, texture);
        }
    }

    void Material::unbind()
    {
        for (auto& [id, texture] : textures)
        {
            texture->unbind();
        }
    }

    #pragma warning(push)
    #pragma warning(disable: 4307) // stdex::hash uses integer overflow as a feature
    UniformValue get_xml_uniform(const pugi::xml_node& xnode)
    {
        auto xtype = xnode.attribute("type");
        if (!xtype)
        {
            PKZO_THROW(std::runtime_error, "Uniform tag without type.");
        }

        // check
        switch (stdex::hash(xtype.as_string()))
        {
            case stdex::hash("bool"):
            case stdex::hash("int"):
            case stdex::hash("uint"):
            case stdex::hash("float"):
                if (!xnode.attribute("value"))
                {
                    PKZO_THROW(std::runtime_error, compose("Uniform %0 has no attribute value.", xnode.attribute("id").as_string()));
                }
                break;
            case stdex::hash("ivec4"):
            case stdex::hash("uvec4"):
            case stdex::hash("vec4"):
                if (!xnode.attribute("w"))
                {
                    PKZO_THROW(std::runtime_error, compose("Uniform %0 has no attribute w.", xnode.attribute("id").as_string()));
                }
                // fallthrough
            case stdex::hash("ivec3"):
            case stdex::hash("uvec3"):
            case stdex::hash("vec3"):
                if (!xnode.attribute("z"))
                {
                    PKZO_THROW(std::runtime_error, compose("Uniform %0 has no attribute z.", xnode.attribute("id").as_string()));
                }
                // fallthrough
            case stdex::hash("ivec2"):
            case stdex::hash("uvec2"):
            case stdex::hash("vec2"):
                if (!xnode.attribute("x"))
                {
                    PKZO_THROW(std::runtime_error, compose("Uniform %0 has no attribute x.", xnode.attribute("id").as_string()));
                }
                if (!xnode.attribute("y"))
                {
                    PKZO_THROW(std::runtime_error, compose("Uniform %0 has no attribute y.", xnode.attribute("id").as_string()));
                }
                break;
            default:
                PKZO_THROW(std::runtime_error, compose("Uniform %0 is of unknown type %1.", xnode.attribute("id").as_string(), xtype.as_string()));
                break;
        }

        // extract
        auto value = UniformValue{};
        switch (stdex::hash(xtype.as_string()))
        {
            case stdex::hash("bool"):
                value = xnode.attribute("value").as_bool();
                break;
            case stdex::hash("int"):
                value = xnode.attribute("value").as_int();
                break;
            case stdex::hash("uint"):
                value = xnode.attribute("value").as_uint();
                break;
            case stdex::hash("float"):
                value = xnode.attribute("value").as_float();
                break;
            case stdex::hash("ivec2"):
                value = glm::ivec2{xnode.attribute("x").as_int(),
                                   xnode.attribute("y").as_int()};
                break;
            case stdex::hash("uvec2"):
                value = glm::uvec2{xnode.attribute("x").as_uint(),
                                   xnode.attribute("y").as_uint()};
                break;
            case stdex::hash("vec2"):
                value = glm::vec2{xnode.attribute("x").as_float(),
                                  xnode.attribute("y").as_float()};
                break;
            case stdex::hash("ivec3"):
                value = glm::ivec3{xnode.attribute("x").as_int(),
                                   xnode.attribute("y").as_int(),
                                   xnode.attribute("z").as_int()};
                break;
            case stdex::hash("uvec3"):
                value = glm::uvec3{xnode.attribute("x").as_uint(),
                                   xnode.attribute("y").as_uint(),
                                   xnode.attribute("z").as_uint()};
                break;
            case stdex::hash("vec3"):
                value = glm::vec3{xnode.attribute("x").as_float(),
                                  xnode.attribute("y").as_float(),
                                  xnode.attribute("z").as_float()};
                break;
            case stdex::hash("ivec4"):
                value = glm::ivec4{xnode.attribute("x").as_int(),
                                   xnode.attribute("y").as_int(),
                                   xnode.attribute("z").as_int(),
                                   xnode.attribute("w").as_int()};
                break;
            case stdex::hash("uvec4"):
                value = glm::uvec4{xnode.attribute("x").as_uint(),
                                   xnode.attribute("y").as_uint(),
                                   xnode.attribute("z").as_uint(),
                                   xnode.attribute("w").as_uint()};
                break;
            case stdex::hash("vec4"):
                value = glm::vec4{xnode.attribute("x").as_float(),
                                  xnode.attribute("y").as_float(),
                                  xnode.attribute("z").as_float(),
                                  xnode.attribute("w").as_float()};
                break;
            default:
                PKZO_ASSERT(false && "This should not happen.");
                break;
        }

        return value;
    }
    #pragma warning(pop)

    void Material::load(const fs::path& file)
    {
        auto tmp = Material{};
        auto dir = file.parent_path();

        auto xdoc = pugi::xml_document{};
        auto result = xdoc.load_file(file.c_str());
        if (!result)
        {
            PKZO_THROW(std::runtime_error, result.description());
        }

        auto xuniform_result = xdoc.select_nodes("/material/uniforms/uniform");
        for (auto& result_node : xuniform_result)
        {
            auto xid = result_node.node().attribute("id");
            if (!xid)
            {
                PKZO_THROW(std::runtime_error, "Uniform tag without id.");
            }

            tmp.set_uniform(xid.as_string(), get_xml_uniform(result_node.node()));
        }

        auto xtexture_result = xdoc.select_nodes("/material/textures/texture");
        for (auto& result_node : xtexture_result)
        {
            auto xid = result_node.node().attribute("id");
            if (!xid)
            {
                PKZO_THROW(std::runtime_error, "Texture tag without id.");
            }
            auto xsrc = result_node.node().attribute("src");
            if (!xsrc)
            {
                PKZO_THROW(std::runtime_error, compose("Texture %0 tag without src.", xid.as_string()));
            }
            auto texture = std::make_shared<Texture>(dir / xsrc.as_string()); // this throws
            tmp.set_texture(xid.as_string(), texture);
        }

        auto xshader_result = xdoc.select_node("/material/shader");
        if (!xshader_result)
        {
            PKZO_THROW(std::runtime_error, compose("Material %0 has no shder.", file.string()));
        }
        auto xshader_src = xshader_result.node().attribute("src");
        if (!xshader_result)
        {
            PKZO_THROW(std::runtime_error, compose("Material %0: Shader has no src attribute.", file.string()));
        }
        auto shader = std::make_shared<Shader>(dir / xshader_src.as_string());
        tmp.set_shader(shader);

        tmp.swap(*this);
    }
}
