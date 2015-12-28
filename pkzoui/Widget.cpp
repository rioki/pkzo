
#include "Widget.h"

namespace pkzoui
{
    Widget::Widget()
    : x(0), y(0), width(15), height(15) {}

    Widget::~Widget() {}

    void Widget::set_position(unsigned int _x, unsigned int _y)
    {
        x = _x;
        y = _y;
    }

    unsigned int Widget::get_x() const
    {
        return x;
    }

    unsigned int Widget::get_y() const
    {
        return y;
    }

    void Widget::set_size(unsigned int _width, unsigned int _height)
    {
        width  = _width;
        height = _height;
    }

    unsigned int Widget::get_width() const
    {
        return width;
    }

    unsigned int Widget::get_height() const
    {
        return height;
    }

    void Widget::handle_mouse_down(unsigned int button, unsigned int x, unsigned int y) {}

    void Widget::handle_mouse_up(unsigned int button, unsigned int x, unsigned int y) {}
}
