
#include "Screen.h"

#include <pkzo/Texture.h>

#include "Canvas.h"
#include "Widget.h"

namespace pkzo
{
    Screen::Screen(const ivec2& s)
    : size(s), background_color(0x0000000) {}

    Screen::~Screen() {}

    void Screen::set_size(const ivec2& value)
    {
        size = value;
    }

    const ivec2& Screen::get_size() const
    {
        return size;
    }

    void Screen::set_background_color(const vec4& value)
    {
        background_color = value;
    }

    const vec4& Screen::get_background_color() const
    {
        return background_color;
    }

    void Screen::set_background_texture(std::shared_ptr<Texture> value)
    {
        background_texture = value;
    }

    std::shared_ptr<Texture> Screen::get_background_texture() const
    {
        return background_texture;
    }

    void Screen::add_widget(Widget& widget)
    {
        widgets.push_back(&widget);
    }

    void Screen::remove_widget(Widget& widget)
    {
        auto i = std::find(widgets.begin(), widgets.end(), &widget);
        if (i != widgets.end())
        {
            widgets.erase(i);
        }
        else
        {
            throw std::logic_error("widget not in screen");
        }
    }

    void Screen::draw(Canvas& canvas) const
    {
        canvas.set_size(size);

        if (background_texture)
        {
            canvas.draw_rectangle(ivec2(0, 0), size, background_color, *background_texture);
        }
        else
        {
            canvas.draw_rectangle(ivec2(0, 0), size, background_color);
        }

        for (const Widget* widget : widgets)
        {
            widget->draw(canvas, ivec2(0, 0));
        }
    }

    void Screen::handle_mouse_move(ivec2 pos, ivec2 mov)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_move(pos, mov);
        }
    }
    
    void Screen::handle_mouse_press(unsigned int button, ivec2 pos)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_press(button, pos);
        }
    }

    void Screen::handle_mouse_release(unsigned int button, ivec2 pos)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_release(button, pos);
        }
    }
}
