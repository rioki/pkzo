
#ifndef _PKZOUI_IMAGE_H_
#define _PKZOUI_IMAGE_H_

#include "Widget.h"

#include <memory>
#include <pkzo/Texture.h>

namespace pkzoui
{
    class PKZOUI_EXPORT Image : public Widget
    {
    public:

        Image();

        ~Image();

        void set_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_texture() const;

        void draw(ScreenRenderer& renderer) const override;        

    private:
        std::shared_ptr<pkzo::Texture> texture;
    };
}

#endif
