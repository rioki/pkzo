
#ifndef _PKZOUI_SCREEN_RENDERER_H_
#define _PKZOUI_SCREEN_RENDERER_H_

#include "defines.h"
#include "Shader.h"
#include "Mesh.h"


namespace pkzo
{
    class Vector2;
    class Color;
    class Texture;

    class PKZO_EXPORT ScreenRenderer
    {
    public:
        ScreenRenderer();

        ScreenRenderer(const ScreenRenderer&) = delete;

        virtual ~ScreenRenderer();

        const ScreenRenderer& operator = (const ScreenRenderer&) = delete;

        void start(const Vector2& size);

        void draw_texture(const Vector2& pos, const Color& color, const Texture& texture);

        void draw_rect(const Vector2& pos, const Vector2& size, const Color& color);

        void draw_rect(const Vector2& pos, const Vector2& size, const Color& color, const Texture& texture);
        

    private:
        pkzo::Shader shader;
        pkzo::Mesh   mesh;

        float projectionMatrix[16];
        float modelViewMatrix[16];
    };
}

#endif

