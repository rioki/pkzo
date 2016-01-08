
#ifndef _PKZO_LIBRARY_H_
#define _PKZO_LIBRARY_H_

#include <memory>
#include <tuple>
#include <map>

#include "defines.h"

namespace pkzo
{
    class Texture;
    class Font;
    class Mesh;
    class Material;

    class PKZO_EXPORT Library
    {
    public:
        Library();

        ~Library();

        std::shared_ptr<Texture> load_texture(const std::string& file);

        std::shared_ptr<Font> load_font(const std::string& file, unsigned int size);

        std::shared_ptr<Mesh> load_mesh(const std::string& file);

        std::shared_ptr<Material> load_material(const std::string& file);

    private:
        typedef std::tuple<std::string, unsigned int> FontId;
        
        std::map<std::string, std::shared_ptr<Texture>>  textures;
        std::map<FontId, std::shared_ptr<Font>>          fonts;
        std::map<std::string, std::shared_ptr<Mesh>>     meshes;
        std::map<std::string, std::shared_ptr<Material>> materials;
        
    };
}

#endif
