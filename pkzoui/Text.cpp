
#include "Text.h"

#include "ScreenRenderer.h"

namespace pkzoui
{
    Text::Text()
    : dirty(true) {}

    Text::~Text() {}

    void Text::set_font(std::shared_ptr<pkzo::Font> value)
    {
        font  = value;
        dirty = true;

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

    void Text::set_color(const Color& value)
    {
        color = value;
    }

    const Color& Text::get_color() const
    {
        return color;
    }

    void Text::draw(ScreenRenderer& renderer) const
    {
        if (dirty)
        {
            texture = font->render(text);
            dirty = false;
        }

        renderer.draw_rect(x, y, width, height, color, &texture);
    }
}
