
#include "Button.h"

#include "ScreenRenderer.h"

namespace pkzo 
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
            size = Vector2((float)background->get_width(), (float)background->get_height());
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
        Vector2 ds = Vector2((float)caption_texture.get_width(), (float)caption_texture.get_height());

        renderer.draw_rect(position, size, background_color, *background);
        renderer.draw_rect(position + ds * 0.5f, Vector2((float)caption_texture.get_width(), (float)caption_texture.get_height()), color, caption_texture);
    }

    void Button::on_click(std::function<void ()> cb)
    {
        click_cb = cb;
    }

    void Button::handle_mouse_up(unsigned int button, Vector2 pos)
    {
        if (button == 1 && pos[0] > position[0] && pos[1] > position[1] && pos[0] < position[0] + size[0] && pos[1] < position[1] + size[1])
        {
            if (click_cb)
            {
                click_cb();
            }
        }
    }
}