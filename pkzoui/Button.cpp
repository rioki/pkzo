
#include "Button.h"

#include "ScreenRenderer.h"

namespace pkzoui 
{
    Button::Button() 
    : caption_dirty(true) {}

    Button::~Button() {}

    void Button::set_caption(const std::string& value)
    {
        caption = value;
        caption_dirty = true;
    }

    const std::string& Button::get_caption() const
    {
        return caption;
    }

    void Button::set_font(std::shared_ptr<pkzo::Font> value)
    {
        font = value;
        caption_dirty = true;
    }

    std::shared_ptr<pkzo::Font> Button::get_font() const
    {
        return font;
    }

    void Button::set_color(const Color& value)
    {
        color = value;
    }

    const Color& Button::get_color() const
    {
        return color;
    }

    void Button::set_background(std::shared_ptr<pkzo::Texture> value)
    {
        background = value;
        if (background)
        {
            width  = background->get_width();
            height = background->get_height();
        }
    }

    std::shared_ptr<pkzo::Texture> Button::get_background() const
    {
        return background;
    }

    void Button::set_background_color(const Color& value)
    {
        background_color = value;
    }

    const Color& Button::get_background_color() const
    {
        return background_color;
    }

    void Button::draw(ScreenRenderer & renderer) const
    {
        if (caption_dirty && font)
        {
            caption_texture = font->render(caption);
            caption_dirty = false;
        }

        // assume the caption is smaller than the width
        unsigned int dx = width  - caption_texture.get_width();
        unsigned int dy = height - caption_texture.get_height();

        renderer.draw_rect(x, y, width, height, background_color, background.get());
        renderer.draw_rect(x + dx/2, y + dy/2, caption_texture.get_width(), caption_texture.get_height(), color, &caption_texture);
    }

    void Button::on_click(std::function<void ()> cb)
    {
        click_cb = cb;
    }

    void Button::handle_mouse_down(unsigned int button, unsigned int x, unsigned int y)
    {

    }

    void Button::handle_mouse_up(unsigned int button, unsigned int bx, unsigned int by)
    {
        if (bx > x && by > y && bx < x + width && by < y + width)
        {
            if (click_cb)
            {
                click_cb();
            }
        }
    }
}