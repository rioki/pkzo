
#ifndef _PKZOUI_SCREEN_RENDERER_H_
#define _PKZOUI_SCREEN_RENDERER_H_

#include "defines.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace pkzo
{
    class PKZO_EXPORT ScreenRenderer
    {
    public:
        ScreenRenderer();

        ScreenRenderer(const ScreenRenderer&) = delete;

        virtual ~ScreenRenderer();

        const ScreenRenderer& operator = (const ScreenRenderer&) = delete;

        void start(unsigned int w, unsigned int h);

        void draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const float* color, const pkzo::Texture* texture);

    private:
        pkzo::Shader shader;
        pkzo::Mesh   mesh;

        float projectionMatrix[16];
        float modelViewMatrix[16];
    };
}

#endif

