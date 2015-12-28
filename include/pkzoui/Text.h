
#ifndef _PKZOUI_TEXT_H_
#define _PKZOUI_TEXT_H_

#include "Widget.h"

#include <memory>
#include <string>
#include <tuple>
#include <pkzo/Font.h>
#include <pkzo/Texture.h>

namespace pkzoui
{
    class PKZOUI_EXPORT Text : public Widget
    {
    public:
        
        Text();

        ~Text();

        void set_font(std::shared_ptr<pkzo::Font> value);

        std::shared_ptr<pkzo::Font> get_font() const;

        void set_text(const std::string& value);

        const std::string& get_text() const;

        void set_color(float r, float g, float b, float a);

        std::tuple<float, float, float, float> get_color() const;

        void draw(ScreenRenderer& renderer) const override;

    private:
        std::shared_ptr<pkzo::Font> font;
        std::string                 text;
        float                       color[4];

        mutable bool          dirty;
        mutable pkzo::Texture texture;
    };
}

#endif

