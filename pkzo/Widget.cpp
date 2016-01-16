
#include "Widget.h"

namespace pkzo
{
    Widget::Widget()
    : position(0, 0), size(15, 15) {}

    Widget::~Widget() {}

    void Widget::set_position(const Vector2& value)
    {
        position = value;
    }

    const Vector2& Widget::get_position() const
    {
        return position;
    }

    void Widget::set_size(const Vector2& value)
    {
        size = value;
    }

    const Vector2& Widget::get_size() const
    {
        return size;
    }

    void Widget::draw(ScreenRenderer& renderer) const {}

    void Widget::handle_mouse_move(Vector2 pos, Vector2 mov) {}

    void Widget::handle_mouse_down(unsigned int button, Vector2 pos) {}

    void Widget::handle_mouse_up(unsigned int button, Vector2 pos) {}
}
