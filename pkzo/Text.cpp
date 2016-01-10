
#include "Text.h"

#include <algorithm>

#include "strex.h"
#include "ScreenRenderer.h"

namespace pkzo
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
            estimate();
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
            estimate();
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
            auto lines = strex::explode(text, "\n");
            textures.resize(lines.size());
            for (unsigned int i = 0; i < lines.size(); i++)
            {
                textures[i] = font->render(lines[i]);
            }
            dirty = false;
        }

        
        // TODO aligment
        Vector2 p2 = position;
        for (auto& texture : textures)
        {
            renderer.draw_rect(p2, Vector2((float)texture.get_width(), (float)texture.get_height()), color, texture);
            p2[1] += texture.get_height();
        }
    }

    void Text::estimate()
    {
        auto lines = strex::explode(text, "\n");
        Vector2 result(0, 0);
        for (auto& line : lines)
        {
            unsigned int w, h;
            std::tie(w, h) = font->estimate(line);
            result[0] = std::max(result[0], (float)w);

            result[1] += h;
        }

        size = result;        
    }
}
