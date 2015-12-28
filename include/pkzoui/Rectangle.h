
#ifndef _PKZOUI_RECTANGLE_H_
#define _PKZOUI_RECTANGLE_H_

#include "Widget.h"

#include <memory>
#include <pkzo/Texture.h>

#include "Color.h"

namespace pkzoui
{
    class PKZOUI_EXPORT Rectangle : public Widget
    {
    public:

        Rectangle();

        ~Rectangle();

        void set_color(const Color& value);

        const Color& get_color() const;

        void set_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_texture() const;

        void draw(ScreenRenderer& renderer) const override;        

    private:
        Color                          color;
        std::shared_ptr<pkzo::Texture> texture;
    };
}

#endif
