// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "ScreenRenderer.h"

#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include <magic_enum/magic_enum.hpp>
#include <tinyformat.h>

#include "resources.h"
#include <pkzo/OpenGLMesh.h>
#include "Shape.h"

namespace pkzo
{
    // TODO: Move the entire concept of includes to Shader
    std::string expand_includes(const std::string_view src, int depth = 0);

    ScreenRenderer::ScreenRenderer(const glm::vec2& size)
    {
        auto hs = size * 0.5f;
        projection_matrix = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);
    }

    ScreenRenderer::~ScreenRenderer() = default;

    void ScreenRenderer::resize(const glm::vec2& size)
    {
        auto hs = size * 0.5f;
        projection_matrix = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);
    }

    void ScreenRenderer::add(Shape* shape)
    {
        shapes.push_back(shape);
    }

    void ScreenRenderer::remove(Shape* shape)
    {
        std::erase(shapes, shape);
    }

    void ScreenRenderer::render(pkzo::GraphicContext& gc)
    {
        if (shapes.empty())
        {
            return;
        }

        using enum UniformLocation;

        if (!screen_shader)
        {
            screen_shader = gc.compile({
                .vertex   = expand_includes(get_resource("Screen.vert")),
                .fragment = expand_includes(get_resource("Screen.frag")),
            });
        }

        gc.start_pass("Screen", screen_shader);
        gc.set_blend_mode(pkzo::BlendMode::ALPHA);
        gc.set_depth_test(pkzo::DepthTest::DISABLED);

        gc.set_uniform(std::to_underlying(PROJECTION_MATRIX), projection_matrix);
        gc.set_uniform(std::to_underlying(VIEW_MATRIX),       view_matrix);

        for (const auto* shape : shapes)
        {
            gc.set_uniform(std::to_underlying(MODEL_MATRIX), shape->get_model_matrix());

            gc.set_uniform(std::to_underlying(BASE_COLOR_FACTOR), shape->get_color());
            gc.set_uniform(std::to_underlying(BASE_COLOR_MAP),    0);

            gc.bind_texture(0, shape->get_texture());

            gc.draw(shape->get_mesh());
        }

        gc.end_pass();
    }
}
