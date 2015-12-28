
#ifndef _PKZOUI_BUTTON_H_
#define _PKZOUI_BUTTON_H_

#include "Widget.h"

#include <memory>
#include <string>
#include <functional>

#include <pkzo/Font.h>
#include <pkzo/Texture.h>

#include "Color.h"

namespace pkzoui
{
    class PKZOUI_EXPORT Button : public Widget
    {
    public:
        Button();

        ~Button();

        void set_caption(const std::string& value);

        const std::string& get_caption() const;

        void set_font(std::shared_ptr<pkzo::Font> value);

        std::shared_ptr<pkzo::Font> get_font() const;

        void set_color(const Color& value);

        const Color& get_color() const;

        void set_background(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background() const;

        void set_background_color(const Color& value);

        const Color& get_background_color() const;

        void draw(ScreenRenderer & renderer) const override;

        void on_click(std::function<void ()> cb);

        void handle_mouse_down(unsigned int button, unsigned int x, unsigned int y) override;

        void handle_mouse_up(unsigned int button, unsigned int x, unsigned int y) override;

    private:
        std::string                    caption;
        std::shared_ptr<pkzo::Font>    font;
        Color                          color;
        std::shared_ptr<pkzo::Texture> background;
        Color                          background_color;
        std::function<void ()>         click_cb;

        mutable bool          caption_dirty;
        mutable pkzo::Texture caption_texture;

        
    };
}

#endif
