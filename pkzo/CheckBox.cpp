#include "CheckBox.h"

#include <algorithm>

#include "ScreenRenderer.h"

namespace pkzo 
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
        
        float dby = (size[1] - background->get_height()) / 2.0f;
        float dmy = (size[1] - mark->get_height()) / 2.0f;
        float dcy = (size[1] - caption_texture.get_height()) / 2.0f;

        renderer.draw_texture(position + Vector2(0, dby), background_color, *background);
        if (checked)
        {
            renderer.draw_texture(position + Vector2(0, dmy), mark_color, *mark);    
        }
        renderer.draw_texture(position + Vector2((float)background->get_width(), dcy), color, caption_texture);
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


    void CheckBox::handle_mouse_up(unsigned int button, Vector2 pos)
    {
        if (button == 1 && pos[0] > position[0] && pos[1] > position[1] && pos[0] < position[0] + size[0] && pos[1] < position[1] + size[1])
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
            size[0] = (float)background->get_width() + (float)cw;
            size[1] = (float)std::max(ch, background->get_height());
        }
    }
}
