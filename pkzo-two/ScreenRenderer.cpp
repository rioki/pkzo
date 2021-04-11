//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "ScreenRenderer.h"

#ifdef _WIN32
#include "resource.h"
#endif

namespace pkzo::two
{
    #ifdef _WIN32
    std::string LoadTextResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType)
    {
        HRSRC   hRSrc = FindResource(hModule, lpName, lpType);
        assert(hRSrc);
        HGLOBAL hGlobal = LoadResource(hModule, hRSrc);
        assert(hGlobal);
        DWORD   nSize = SizeofResource(hModule, hRSrc);
        const char* psCode = (const char*)LockResource(hGlobal);
        return std::string(psCode, nSize);
    }
    #endif

    std::unique_ptr<Mesh> make_unit_rectangle()
    {
        auto mesh = std::make_unique<Mesh>();

        mesh->add_vertex({-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f});
        mesh->add_vertex({ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f});

        mesh->add_triangle({0, 1, 2});
        mesh->add_triangle({2, 3, 0});

        return mesh;
    }

    ScreenRenderer::ScreenRenderer() noexcept
    {

        #ifdef _WIN32
        HMODULE hModule = GetModuleHandle(_T("pkzo-two.dll"));
        auto vertex_code   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SCREEN_VERT), _T("GLSL"));
        auto fragment_code = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SCREEN_FRAG), _T("GLSL"));
        shader = std::make_unique<Shader>(vertex_code, fragment_code);
        #else
        #error Port ME
        #endif
        rectangle = make_unit_rectangle();
    }

    ScreenRenderer::~ScreenRenderer() = default;

    void ScreenRenderer::start(const glm::vec2& size) noexcept
    {
        assert(shader);
        assert(rectangle);

        auto hs = size / 2.0f;

        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "ScreenRenderer");
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        // TMP
        glDisable(GL_CULL_FACE);

        shader->bind();
        shader->set_uniform("pkzo_ProjectionMatrix", glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f));
        shader->set_uniform("pkzo_ViewMatrix", glm::mat4(1.0f));

        rectangle->bind(*shader);
    }

    void ScreenRenderer::draw_rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture) noexcept
    {
        assert(shader);
        assert(rectangle);

        auto model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(position, 0.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(size, 1.0f));

        shader->set_uniform("pkzo_ModelMatrix", model_matrix);

        shader->set_uniform("pkzo_BaseColorFactor", color);
        if (texture)
        {
            shader->set_uniform("pkzo_HasBaseColorMap", true);
            shader->set_uniform("pkzo_BaseColorMap", texture);
        }
        else
        {
            shader->set_uniform("pkzo_HasBaseColorMap", false);
        }

        rectangle->draw();
    }

    void ScreenRenderer::finalize() noexcept
    {
        glPopDebugGroup();
    }
}
