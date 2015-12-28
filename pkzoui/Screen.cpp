
#include "Screen.h"

#include "ScreenRenderer.h"
#include "Widget.h"

namespace pkzoui
{
    Screen::Screen(unsigned int w, unsigned int h)
    : width(w), height(h) 
    {

    }

    Screen::~Screen() {}

    void Screen::set_size(unsigned int _width, unsigned int _height)
    {
        width  = _width;
        height = _height;
    }

    unsigned int Screen::get_width() const
    {
        return width;
    }

    unsigned int Screen::get_height() const
    {
        return height;
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
        renderer.start(width, height);

        renderer.draw_rect(0, 0, width, height, background_color, background_texture.get());

        for (const Widget* widget : widgets)
        {
            widget->draw(renderer);
        }
    }

    void Screen::handle_mouse_down(unsigned int button, unsigned int x, unsigned int y)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_down(button, x, y);
        }
    }

    void Screen::handle_mouse_up(unsigned int button, unsigned int x, unsigned int y)
    {
        for (Widget* widget : widgets)
        {
            widget->handle_mouse_up(button, x, y);
        }
    }
}
