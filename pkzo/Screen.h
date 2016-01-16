
#ifndef _PKZOUI_SCREEN_H_
#define _PKZOUI_SCREEN_H_

#include "defines.h"

#include <memory>
#include <tuple>
#include <list>

#include "Texture.h"
#include "Color.h"
#include "Vector2.h"

namespace pkzo
{
    class Widget;
    class ScreenRenderer;

    class PKZO_EXPORT Screen
    {
    public:
        Screen(const Vector2& size);

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;

        void set_size(const Vector2& value);

        const Vector2& get_size() const;

        void set_background_color(const Color& value);

        const Color& get_background_color() const;

        void set_background_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background_texture() const;

        void add_widget(Widget& widget);

        void remove_widget(Widget& widget);

        virtual void draw(ScreenRenderer& renderer) const;

        virtual void handle_mouse_move(Vector2 pos, Vector2 mov);

        virtual void handle_mouse_down(unsigned int button, Vector2 pos);

        virtual void handle_mouse_up(unsigned int button, Vector2 pos);

    private:
        Vector2 size;

        std::list<Widget*> widgets;

        Color                          background_color;
        std::shared_ptr<pkzo::Texture> background_texture;
    };
}

#endif
