
#ifndef _PKZOUI_SCREEN_H_
#define _PKZOUI_SCREEN_H_

#include "defines.h"

#include <memory>
#include <tuple>
#include <list>

#include "Texture.h"
#include "Color.h"

namespace pkzo
{
    class Widget;
    class ScreenRenderer;

    class PKZO_EXPORT Screen
    {
    public:
        Screen(unsigned int width, unsigned int height);

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;

        void set_size(unsigned int width, unsigned int height);

        unsigned int get_width() const;

        unsigned int get_height() const;

        void set_background_color(const Color& value);

        const Color& get_background_color() const;

        void set_background_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background_texture() const;

        void add_widget(Widget& widget);

        void remove_widget(Widget& widget);

        virtual void draw(ScreenRenderer& renderer) const;

        virtual void handle_mouse_move(unsigned int x, unsigned int y, int dx, int dy);

        virtual void handle_mouse_down(unsigned int button, unsigned int x, unsigned int y);

        virtual void handle_mouse_up(unsigned int button, unsigned int x, unsigned int y);

    private:
        unsigned int width;
        unsigned int height;

        std::list<Widget*> widgets;

        Color                          background_color;
        std::shared_ptr<pkzo::Texture> background_texture;
    };
}

#endif
