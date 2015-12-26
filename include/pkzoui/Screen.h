
#ifndef _PKZOUI_SCREEN_H_
#define _PKZOUI_SCREEN_H_

#include <memory>
#include <tuple>

#include <pkzo/Texture.h>

#include "defines.h"

namespace pkzoui
{
    class ScreenRenderer;

    class PKZOUI_EXPORT Screen
    {
    public:
        Screen(unsigned int width, unsigned int height);

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;

        void set_background_color(float r, float g, float b, float a);

        std::tuple<float, float, float, float> get_background_color() const;

        void set_background_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_background_texture() const;

        void draw(ScreenRenderer& renderer);

    private:
        unsigned int width;
        unsigned int height;

        float background_color[4];
        std::shared_ptr<pkzo::Texture> background_texture;
    };
}

#endif
