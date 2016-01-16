
#include "Rectangle.h"

#include "ScreenRenderer.h"

namespace pkzo
{        
    Rectangle::Rectangle() {}

    Rectangle::~Rectangle() {}

    void Rectangle::set_color(const Color& value)
    {
        color = value;
    }

    const Color& Rectangle::get_color() const
    {
        return color;
    }

    void Rectangle::set_texture(std::shared_ptr<pkzo::Texture> value)
    {
        texture = value;
        if (texture)
        {
            set_size(Vector2(texture->get_width(), texture->get_height()));
        }
    }

    std::shared_ptr<pkzo::Texture> Rectangle::get_texture() const
    {
        return texture;
    }

    void Rectangle::draw(ScreenRenderer& renderer) const
    {
        if (texture)
        {
            renderer.draw_rect(position, size, color, *texture);
        }
        else
        {
            renderer.draw_rect(position, size, color);
        }
    }
}
