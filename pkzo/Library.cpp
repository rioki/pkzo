
#include "Library.h"

#include "Texture.h"
#include "Font.h"
#include "Mesh.h"
#include "Material.h"

namespace pkzo
{
    Library::Library() {}

    Library::~Library() {}

    std::shared_ptr<Texture> Library::load_texture(const std::string& file)
    {
        auto i = textures.find(file);
        if (i != textures.end())
        {
            return i->second;
        }
        else
        {
            std::shared_ptr<Texture> texture(new Texture);
            texture->load(file);
            textures[file] = texture;
            return texture;
        }
    }

    std::shared_ptr<Font> Library::load_font(const std::string& file, unsigned int size)
    {
        FontId id(file, size);
        auto i = fonts.find(id);
        if (i != fonts.end())
        {
            return i->second;
        }
        else
        {
            std::shared_ptr<Font> font(new Font);
            font->load(file, size);
            fonts[id] = font;
            return font;
        }
    }   

    std::shared_ptr<Mesh> Library::load_mesh(const std::string& file)
    {
        auto i = meshes.find(file);
        if (i != meshes.end())
        {
            return i->second;
        }
        else
        {
            std::shared_ptr<Mesh> mesh(new Mesh);
            mesh->load(file);
            meshes[file] = mesh;
            return mesh;
        }
    }

    std::shared_ptr<Material> Library::load_material(const std::string& file)
    {
        auto i = materials.find(file);
        if (i != materials.end())
        {
            return i->second;
        }
        else
        {
            std::shared_ptr<Material> material(new Material);
            material->load(file);
            materials[file] = material;
            return material;
        }
    }
}
