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

#pragma once

#include <memory>

#include <pkzo/GraphicContext.h>
#include <pkzo/Shader.h>
#include <pkzo/Mesh.h>

#include "api.h"

namespace pkzo2d
{
    class Shape;
    using pkzo::Shader;
    using pkzo::Mesh;

    class PKZO2D_EXPORT Renderer
    {
    public:
        Renderer(const glm::vec2& size);

        ~Renderer();

        void resize(const glm::vec2& size);

        void add(Shape* shape);
        void remove(Shape* shape);

        void render(pkzo::GraphicContext& gc);

    private:
        glm::mat4 projection_matrix;
        glm::mat4 view_matrix       = glm::mat4(1.0f);

        std::vector<Shape*>     shapes;

        std::shared_ptr<Shader> screen_shader;

        Renderer(const Renderer&) = delete;
        Renderer& operator = (const Renderer&) = delete;
    };
}
