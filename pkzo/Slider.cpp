
#include "Slider.h"

#include "ScreenRenderer.h"

namespace pkzo
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
            size = Vector2((float)background->get_width(), (float)background->get_height());
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
        float nx = static_cast<float>(dw) * (static_cast<float>(value) / static_cast<float>(increments - 1));
        
        // assume nob.height == background.height
        renderer.draw_rect(position, size, background_color, *background);
        renderer.draw_rect(position + Vector2(nx, 0), Vector2((float)nob->get_width(), (float)nob->get_height()), nob_color, *nob);
    }

    void Slider::handle_mouse_move(Vector2 pos, Vector2 mov) 
    {
        if (active && pos[0] > position[0] && pos[0] < position[0] + size[0])
        {
            float dw = pos[0] - position[0];
            value = static_cast<unsigned int>((dw / size[0]) * increments);

            if (change_cb)
            {
                change_cb();
            }
        }
    }

    void Slider::handle_mouse_down(unsigned int button, Vector2 pos)
    {
        if (button == 1 && pos[0] > position[0] && pos[1] > position[1] && 
            pos[0] < position[0] + size[0] && pos[1] < position[1] + size[1])
        {
            active = true;

            float dw = pos[0] - position[0];
            value = static_cast<unsigned int>((dw / size[0]) * increments);

            if (change_cb)
            {
                change_cb();
            }
        }
    }

    void Slider::handle_mouse_up(unsigned int button, Vector2 pos)
    {
        if (button == 1)
        {
            active = false;
        }
    }
}
