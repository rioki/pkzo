
#include "Material.h"

#include <pkzo/Shader.h>
#include <pkzo/Texture.h>

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
