
#include "Screen.h"

#include "ScreenRenderer.h"

namespace pkzoui
{
    Screen::Screen(unsigned int w, unsigned int h)
    : width(w), height(h) 
    {
        background_color[0] = 1.0f;
        background_color[1] = 1.0f;
        background_color[2] = 1.0f;
        background_color[3] = 1.0f;
    }

    Screen::~Screen() {}

    void Screen::set_background_color(float r, float g, float b, float a)
    {
        background_color[0] = a;
        background_color[1] = g;
        background_color[2] = b;
        background_color[3] = a;
    }

    std::tuple<float, float, float, float> Screen::get_background_color() const
    {
        return std::make_tuple(background_color[0], background_color[1], background_color[2], background_color[3]);
    }

    void Screen::set_background_texture(std::shared_ptr<pkzo::Texture> value)
    {
        background_texture = value;
    }

    std::shared_ptr<pkzo::Texture> Screen::get_background_texture() const
    {
        return background_texture;
    }

    void Screen::draw(ScreenRenderer& renderer)
    {
        renderer.start(width, height);

        renderer.draw_rect(0, 0, width, height, background_color, background_texture.get());
    }
}
