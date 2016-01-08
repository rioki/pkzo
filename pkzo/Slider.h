
#ifndef _PKZOUI_SLIDER_H_
#define _PKZOUI_SLIDER_H_

#include "Widget.h"

#include <memory>
#include <string>
#include <functional>

#include "Font.h"
#include "Texture.h"
#include "Color.h"

namespace pkzo
{
    class PKZO_EXPORT Slider : public Widget
    {
    public:
        Slider();

        ~Slider();

        void set_value(unsigned int value);

        unsigned int get_value() const;

        void set_increments(unsigned int value);

        unsigned int get_increments() const;

        void set_background(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background() const;

        void set_background_color(const Color& value);

        const Color& get_background_color() const;

        void set_nob(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_nob() const;

        void set_nob_color(const Color& value);

        const Color& get_nob_color() const;

        void on_change(std::function<void ()> cb);

        void draw(ScreenRenderer & renderer) const override;

        void handle_mouse_move(unsigned int x, unsigned int y, int dx, int dy) override;

        void handle_mouse_down(unsigned int button, unsigned int x, unsigned int y) override;

        void handle_mouse_up(unsigned int button, unsigned int x, unsigned int y) override;

    private:
        unsigned int value;
        unsigned int increments;

        std::shared_ptr<pkzo::Texture> background;
        Color                          background_color;
        std::shared_ptr<pkzo::Texture> nob;
        Color                          nob_color;
        
        std::function<void ()> change_cb;

        bool active;
    };
}

#endif
