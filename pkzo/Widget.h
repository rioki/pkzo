
#ifndef _PKZOUI_WIDGET_H_
#define _PKZOUI_WIDGET_H_

#include "defines.h"

#include "Vector2.h"

namespace pkzo
{
    class ScreenRenderer;

    class PKZO_EXPORT Widget
    {
    public:
        Widget();

        Widget(const Widget&) = delete;

        ~Widget();

        const Widget& operator = (const Widget&) = delete;

        void set_position(const Vector2& value);

        const Vector2& get_position() const;

        void set_size(const Vector2& value);

        const Vector2& get_size() const;

        virtual void draw(ScreenRenderer& renderer) const;

        virtual void handle_mouse_move(Vector2 pos, Vector2 mov);

        virtual void handle_mouse_down(unsigned int button, Vector2 pos);

        virtual void handle_mouse_up(unsigned int button, Vector2 pos);

    protected:
        Vector2 position;
        Vector2 size;
    };
}

#endif
