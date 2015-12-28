
#include "Image.h"

#include "ScreenRenderer.h"

namespace pkzoui
{        
    Image::Image() {}

    Image::~Image() {}

    void Image::set_texture(std::shared_ptr<pkzo::Texture> value)
    {
        texture = value;
        if (texture)
        {
            set_size(texture->get_width(), texture->get_height());
        }
    }

    std::shared_ptr<pkzo::Texture> Image::get_texture() const
    {
        return texture;
    }

    void Image::draw(ScreenRenderer& renderer) const
    {
        renderer.draw_rect(x, y, width, height, nullptr, texture.get());
    }
}
