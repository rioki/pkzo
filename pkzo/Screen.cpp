
#include "Screen.h"

#include "ScreenRenderer.h"
#include "Widget.h"

namespace pkzo
{
    Screen::Screen(const Vector2& s)
    : size(s), background_color(0x0000000) {}

    Screen::~Screen() {}

    void Screen::set_size(const Vector2& value)
    {
        size = value;
    }

    const Vector2& Screen::get_size() const
    {
        return size;
    }

    void Screen::set_background_color(const Color& value)
    {
        background_color = value;
    }

    const Color& Screen::get_background_color() const
    {
        return background_color;
    }

    void Screen::set_background_texture(std::shared_ptr<pkzo::Texture> value)
    {
        background_texture = value;
    }

    std::shared_ptr<pkzo::Texture> Screen::get_background_texture() const
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

    void Screen::draw(ScreenRenderer& renderer) const
    {
        renderer.start(size);

        if (background_texture)
        {
            renderer.draw_rect(Vector2(0, 0), size, background_color, *background_texture);
        }
        else
        {
            renderer.draw_rect(Vector2(0, 0), size, background_color);
        }

        for (const Widget* widget : widgets)
        {
            widget->draw(renderer);
        }
    }

    void Screen::handle_mouse_move(Vector2 pos, Vector2 mov)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_move(pos, mov);
        }
    }
    
    void Screen::handle_mouse_down(unsigned int button, Vector2 pos)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_down(button, pos);
        }
    }

    void Screen::handle_mouse_up(unsigned int button, Vector2 pos)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_up(button, pos);
        }
    }
}
