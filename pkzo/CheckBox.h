
#ifndef _PKZOUI_CHECKBOX_H_
#define _PKZOUI_CHECKBOX_H_

#include "Widget.h"

#include <memory>
#include <string>
#include <functional>

#include "Font.h"
#include "Texture.h"
#include "Color.h"

namespace pkzo
{
    class PKZO_EXPORT CheckBox : public Widget
    {
    public:
        CheckBox();

        ~CheckBox();

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

        void set_mark(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_mark() const;

        void set_mark_color(const Color& value);

        const Color& get_mark_color() const;

        void draw(ScreenRenderer & renderer) const override;

        void handle_mouse_up(unsigned int button, unsigned int x, unsigned int y) override;

        void set_checked(bool value);

        bool is_checked() const;
        
        void on_toggle(std::function<void ()> cb);

    private:
        bool checked;

        std::string                    caption;
        std::shared_ptr<pkzo::Font>    font;
        Color                          color;
        std::shared_ptr<pkzo::Texture> background;
        Color                          background_color;
        std::shared_ptr<pkzo::Texture> mark;
        Color                          mark_color;

        std::function<void ()> toggle_cb;

        mutable bool          caption_dirty;
        mutable pkzo::Texture caption_texture;

        void compute_size();
    };
}

#endif
