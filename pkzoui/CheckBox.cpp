#include "CheckBox.h"

#include <algorithm>

#include "ScreenRenderer.h"

namespace pkzoui 
{
    CheckBox::CheckBox() 
    : checked(false), caption_dirty(true) {}

    CheckBox::~CheckBox() {}

    void CheckBox::set_caption(const std::string& value)
    {
        caption = value;
        caption_dirty = true;
        compute_size();
    }

    const std::string& CheckBox::get_caption() const
    {
        return caption;
    }

    void CheckBox::set_font(std::shared_ptr<pkzo::Font> value)
    {
        font = value;
        caption_dirty = true;
        compute_size();
    }

    std::shared_ptr<pkzo::Font> CheckBox::get_font() const
    {
        return font;
    }

    void CheckBox::set_color(const Color& value)
    {
        color = value;
    }

    const Color& CheckBox::get_color() const
    {
        return color;
    }

    void CheckBox::set_background(std::shared_ptr<pkzo::Texture> value)
    {
        background = value;
        compute_size();
    }

    std::shared_ptr<pkzo::Texture> CheckBox::get_background() const
    {
        return background;
    }

    void CheckBox::set_background_color(const Color& value)
    {
        background_color = value;
    }

    const Color& CheckBox::get_background_color() const
    {
        return background_color;
    }

    void CheckBox::set_mark(std::shared_ptr<pkzo::Texture> value)
    {
        mark = value;
    }

    std::shared_ptr<pkzo::Texture> CheckBox::get_mark() const
    {
        return mark;
    }

    void CheckBox::set_mark_color(const Color& value)
    {
        mark_color = value;
    }

    const Color& CheckBox::get_mark_color() const
    {
        return background_color;
    }

    void CheckBox::draw(ScreenRenderer & renderer) const
    {
        if (caption_dirty && font)
        {
            caption_texture = font->render(caption);
            caption_dirty = false;
        }
        
        unsigned int dby = height - background->get_height();
        unsigned int dmy = height - mark->get_height();
        unsigned int dcy = height - caption_texture.get_height();

        renderer.draw_rect(x, y + dby / 2, background->get_width(), background->get_height(), background_color, background.get());
        if (checked)
        {
            renderer.draw_rect(x, y + dmy / 2, mark->get_width(), mark->get_height(), mark_color, mark.get());    
        }
        renderer.draw_rect(x + background->get_width(), y + dcy / 2, caption_texture.get_width(), caption_texture.get_height(), color, &caption_texture);
    }

    void CheckBox::set_checked(bool value)
    {
        checked = value;
    }

    bool CheckBox::is_checked() const
    {
        return checked;
    }
        
    void CheckBox::on_toggle(std::function<void ()> cb)
    {
        toggle_cb = cb;
    }


    void CheckBox::handle_mouse_up(unsigned int button, unsigned int bx, unsigned int by)
    {
        if (button == 1 && bx > x && by > y && bx < x + width && by < y + width)
        {
            checked = !checked;
            if (toggle_cb)
            {
                toggle_cb();
            }
        }
    }

    void CheckBox::compute_size()
    {
        if (font && background)
        {
            unsigned int cw, ch;
            std::tie(cw, ch) = font->estimate(caption);
            width  = background->get_width() + cw;
            height = std::max(ch, background->get_height());
        }
    }
}
