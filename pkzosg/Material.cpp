
#include "Material.h"

#include <fstream>
#include <rjson.h>
#include <pkzo/Shader.h>
#include <pkzo/Texture.h>

#include "compose.h"
#include "path.h"

namespace pkzo
{
    Material::Material() {}
    
    Material::~Material() {}

    void Material::set_color(const Color& value)
    {
        color = value;
    }

    const Color& Material::get_color() const
    {
        return color;
    }

    void Material::set_texture(std::shared_ptr<pkzo::Texture> value)
    {
        texture = value;
    }

    std::shared_ptr<pkzo::Texture> Material::get_texture() const
    {
        return texture;
    }

    void Material::load(const std::string& file)
    {
        std::ifstream in(file);
        if (! in.is_open())
        {
            throw std::runtime_error(compose("Failed to open %0 for reading.", file));
        }
        
        std::string dir = path::dirname(file);

        rjson::Object rmaterial;
        in >> rmaterial;

        if (rmaterial.count("color"))
        {
            rjson::Array rcolor = rmaterial["color"];
            if (rcolor.size() == 4)
            {
                color[0] = rcolor[0];
                color[1] = rcolor[1];
                color[2] = rcolor[2];
                color[3] = rcolor[3];                
            }
            else
            {
                throw std::runtime_error("The color must have 4 components.");
            }
        }
        
        if (rmaterial.count("texture"))
        {
            std::string texture_file = path::join(dir, rmaterial["texture"]);
            std::shared_ptr<pkzo::Texture> t(new pkzo::Texture);
            t->load(texture_file);
            texture = t;
        }
    }

    void Material::setup(Shader& shader) const
    {
        shader.set_uniform("uMaterialColor", color, 3);
        
        if (texture)
        {
            texture->bind(0);

            shader.set_uniform("uMaterialHasTexture", 1);
            shader.set_uniform("uMaterialTexture", 0);
        }
        else
        {
            shader.set_uniform("uMaterialHasTexture", 0);
        }
    }
}
