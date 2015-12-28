
#ifndef _PKZOUI_WIDGET_H_
#define _PKZOUI_WIDGET_H_

#include "defines.h"

namespace pkzoui
{
    class ScreenRenderer;

    class PKZOUI_EXPORT Widget
    {
    public:
        Widget();

        Widget(const Widget&) = delete;

        ~Widget();

        const Widget& operator = (const Widget&) = delete;

        void set_position(unsigned int x, unsigned int y);

        unsigned int get_x() const;

        unsigned int get_y() const;

        void set_size(unsigned int width, unsigned int height);

        unsigned int get_width() const;

        unsigned int get_height() const;

        virtual void draw(ScreenRenderer& renderer) const = 0;

    protected:
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    };
}

#endif
