
#ifndef _PKZOUI_SCREEN_H_
#define _PKZOUI_SCREEN_H_

#include <memory>
#include <tuple>
#include <list>

#include <pkzo/Texture.h>

#include "defines.h"
#include "Color.h"

namespace pkzoui
{
    class Widget;
    class ScreenRenderer;

    class PKZOUI_EXPORT Screen
    {
    public:
        Screen(unsigned int width, unsigned int height);

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;

        void set_background_color(const Color& value);

        const Color& get_background_color() const;

        void set_background_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background_texture() const;

        void add_widget(Widget& widget);

        void remove_widget(Widget& widget);

        void draw(ScreenRenderer& renderer) const;

    private:
        unsigned int width;
        unsigned int height;

        std::list<Widget*> widgets;

        Color                          background_color;
        std::shared_ptr<pkzo::Texture> background_texture;
    };
}

#endif
