
#include "Text.h"

#include "ScreenRenderer.h"

namespace pkzoui
{
    Text::Text()
    : dirty(true) 
    {
        color[0] = 1.0f;
        color[1] = 1.0f;
        color[2] = 1.0f;
        color[3] = 1.0f;
    }

    Text::~Text() {}

    void Text::set_font(std::shared_ptr<pkzo::Font> value)
    {
        font  = value;
        dirty = false;

        if (font)
        {
            std::tie(width, height) = font->estimate(text);
        }
    }

    std::shared_ptr<pkzo::Font> Text::get_font() const
    {
        return font;
    }

    void Text::set_text(const std::string& value)
    {
        text  = value;
        dirty = true;

        if (font)
        {
            std::tie(width, height) = font->estimate(text);
        }
    }

    const std::string& Text::get_text() const
    {
        return text;
    }

    void Text::set_color(float r, float g, float b, float a)
    {
        color[0] = a;
        color[1] = g;
        color[2] = b;
        color[3] = a;
    }

    std::tuple<float, float, float, float> Text::get_color() const
    {
        return std::make_tuple(color[0], color[1], color[2], color[3]);
    }

    void Text::draw(ScreenRenderer& renderer) const
    {
        if (dirty)
        {
            texture = font->render(text);
        }

        renderer.draw_rect(x, y, width, height, color, &texture);
    }
}
