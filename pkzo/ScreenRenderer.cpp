
#include "ScreenRenderer.h"

#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#else
// TODO ezrc
#endif

#include "glt.h"
#include <GL/glew.h>

namespace pkzo
{
    ScreenRenderer::ScreenRenderer()
    {
        mesh.create_plane(1.0f, 1.0f);

        #ifdef _MSC_VER
        HMODULE hModule = GetModuleHandle(_T("pkzo.dll"));

        HRSRC hInterfaceVertex = FindResource(hModule, MAKEINTRESOURCE(IDR_GLSL_INTERFACE_VERTEX), _T("GLSL"));
        HGLOBAL hgInterfaceVertex = LoadResource(hModule, hInterfaceVertex);
        const char* interface_vertex = (const char*)LockResource(hgInterfaceVertex);

        HRSRC hInterfaceFragment = FindResource(hModule, MAKEINTRESOURCE(IDR_GLSL_INTERFACE_FRAGMENT), _T("GLSL"));
        HGLOBAL hgInterfaceFragment = LoadResource(hModule, hInterfaceFragment);
        const char* interface_fragment = (const char*)LockResource(hgInterfaceFragment);
        #else
        // TODO
        #endif

        shader.set_vertex_code(interface_vertex);
        shader.set_fragment_code(interface_fragment);
    }

    ScreenRenderer::~ScreenRenderer() {}

    void ScreenRenderer::start(unsigned int w, unsigned int h)
    {
        gltOrtho2D(projectionMatrix, 0.0f, (float)w, (float)h, 0.0f);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }   

    void ScreenRenderer::draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const float* color, const pkzo::Texture* texture)
    {
        gltLoadIdentity(modelViewMatrix);
        gltTranslate(modelViewMatrix, (float)x, (float)y, 0.0f);
        gltScale(modelViewMatrix, (float)w, (float)h, 1.0f);
        gltTranslate(modelViewMatrix, 0.5f, 0.5f, 0.0f);

        shader.bind();
        shader.set_uniform_matrix("uProjectionMatrix", projectionMatrix, 16);
        shader.set_uniform_matrix("uModelViewMatrix", modelViewMatrix, 16);

        if (color != nullptr)
        {
            shader.set_uniform("uColor", color, 4);
        }
        else
        {
            shader.set_uniform("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
        }

        if (texture != nullptr)
        {
            texture->bind(0);
            shader.set_uniform("uTexture", 0);
            shader.set_uniform("uHasTexture", 1);
        }
        else
        {
            shader.set_uniform("uHasTexture", 0);
        }

        mesh.draw(shader);
    }
}
