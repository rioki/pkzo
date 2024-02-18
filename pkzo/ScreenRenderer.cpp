// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "ScreenRenderer.h"

#include "resource.h"

namespace pkzo
{
    glow::ColorMode to_glow(const pkzo::ColorMode& mode);
    std::string LoadTextResource(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType);

    std::shared_ptr<glow::Texture> upload_texture(const Image& image)
    {
        auto color = to_glow(image.get_color_mode());
        auto type  = glow::DataType::UINT8;

        auto texture = std::make_shared<glow::Texture>();
        texture->upload(image.get_size(), color, type, image.get_data());

        return texture;
    }

    ScreenRenderer::ScreenRenderer()
    : texture_cache(upload_texture)
    {
        static auto handle = GetModuleHandleW(L"pkzo.dll");
        shader.compile(glow::ShaderType::VERTEX, LoadTextResource(handle, MAKEINTRESOURCEW(IDR_GLSL_SCREEN_VERTEX), L"GLSL"));
        shader.compile(glow::ShaderType::FRAGMENT, LoadTextResource(handle, MAKEINTRESOURCEW(IDR_GLSL_SCREEN_FRAGMENT), L"GLSL"));
        shader.link();

        rectangle.upload_values("aPosition", {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0,  1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}
        });
        rectangle.upload_values("aTexCoord", {
            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {1.0,  0.0f},
            {0.0f, 0.0f}
        });
        rectangle.upload_indexes({
            {0, 1, 2},
            {0, 2, 3}
        });

        model_stack.push(glm::mat3(1.0f));
    }

    ScreenRenderer::~ScreenRenderer() = default;

    void ScreenRenderer::start_frame(glm::vec2 size) noexcept
    {
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        auto projection = glm::ortho(0.0f, size.x, size.y, 0.0f, -1.0f, 1.0f);
        auto view       = glm::mat4(1.0f);

        shader.bind();
        shader.set_uniform("uProjection", projection);
        shader.set_uniform("uView", view);
        check(model_stack.size() == 1);


        rectangle.bind(shader);
    }

    void ScreenRenderer::finish_frame() noexcept
    {
        check(model_stack.size() == 1);

        texture_cache.collect();
    }

    void ScreenRenderer::push_model(const glm::mat3& model) noexcept
    {
        check(!model_stack.empty());
        auto final_model = model_stack.top() * model;
        model_stack.push(final_model);
    }

    void ScreenRenderer::pop_model() noexcept
    {
        model_stack.pop();
    }

    void ScreenRenderer::draw_rectangle(const glm::mat3& transform, glm::vec2 size, glm::vec4 color)
    {
        shader.set_uniform("uColor", color);
        shader.set_uniform("uHasTexture", false);

        auto model = model_stack.top() * transform;
        model = glm::scale(model, size);
        shader.set_uniform("uModel", glm::to3d(model));

        rectangle.draw();
    }

    void ScreenRenderer::draw_rectangle(const glm::mat3& transform, glm::vec2 size, glm::vec4 color, const Image& image)
    {
        shader.set_uniform("uColor", color);

        auto texture = texture_cache.get(image);
        texture->bind(0);
        shader.set_uniform("uTexture", 0);
        shader.set_uniform("uHasTexture", true);

        auto model = model_stack.top() * transform;
        model = glm::scale(model, size);
        shader.set_uniform("uModel", glm::to3d(model));

        rectangle.draw();
    }
}
