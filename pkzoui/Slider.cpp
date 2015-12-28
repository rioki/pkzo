
#include "Slider.h"

#include "ScreenRenderer.h"

namespace pkzoui
{
    Slider::Slider()
    : value(0), increments(100), active(false) {}

    Slider::~Slider() {}

    void Slider::set_value(unsigned int v)
    {
        value = v;
    }

    unsigned int Slider::get_value() const
    {
        return value;
    }

    void Slider::set_increments(unsigned int value)
    {
        increments = value;
    }

    unsigned int Slider::get_increments() const
    {
        return increments;
    }

    void Slider::set_background(std::shared_ptr<pkzo::Texture> value)
    {
        background = value;
        if (background)
        {
            width  = background->get_width();
            height = background->get_height();
        }
    }

    std::shared_ptr<pkzo::Texture> Slider::get_background() const
    {
        return background;
    }

    void Slider::set_background_color(const Color& value)
    {
        background_color = value;
    }

    const Color& Slider::get_background_color() const
    {
        return background_color;
    }

    void Slider::set_nob(std::shared_ptr<pkzo::Texture> value)
    {
        nob = value;
    }

    std::shared_ptr<pkzo::Texture> Slider::get_nob() const
    {
        return nob;
    }

    void Slider::set_nob_color(const Color& value)
    {
        nob_color = value;
    }

    const Color& Slider::get_nob_color() const
    {
        return nob_color;
    }

    void Slider::on_change(std::function<void ()> cb)
    {
        change_cb = cb;
    }

    void Slider::draw(ScreenRenderer & renderer) const
    {
        unsigned int dw = background->get_width() - nob->get_width(); 
        unsigned int nx = static_cast<unsigned int>(static_cast<float>(dw) * (static_cast<float>(value) / static_cast<float>(increments - 1)));
        
        // assume nob.height == background.height
        renderer.draw_rect(x, y, width, height, background_color, background.get());
        renderer.draw_rect(x + nx, y, nob->get_width(), nob->get_height(), nob_color, nob.get());
    }

    void Slider::handle_mouse_move(unsigned int bx, unsigned int by, int dx, int dy) 
    {
        if (active && bx > x && bx < x + width)
        {
            unsigned int dw = bx - x;
            value = static_cast<unsigned int>(static_cast<float>(dw) / static_cast<float>(width)* increments);

            if (change_cb)
            {
                change_cb();
            }
        }
    }

    void Slider::handle_mouse_down(unsigned int button, unsigned int bx, unsigned int by)
    {
        if (button == 1 && bx > x && by > y && bx < x + width && by < y + width)
        {
            active = true;

            unsigned int dw = bx - x;
            value = static_cast<unsigned int>(static_cast<float>(dw) / static_cast<float>(width)* increments);

            if (change_cb)
            {
                change_cb();
            }
        }
    }

    void Slider::handle_mouse_up(unsigned int button, unsigned int bx, unsigned int by)
    {
        if (button == 1)
        {
            active = false;
        }
    }
}
