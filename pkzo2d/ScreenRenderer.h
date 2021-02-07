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

#ifndef _PKZO2D_SCREEN_RENDERER_H_
#define _PKZO2D_SCREEN_RENDERER_H_

#include "config.h"

#include <memory>
#include <glm/glm.hpp>
#include <pkzo/pkzo.h>

namespace pkzo2d
{
    using namespace pkzo;

    class PKZO2D_EXPORT ScreenRenderer
    {
    public:
        ScreenRenderer() noexcept;
        ScreenRenderer(const ScreenRenderer&) = delete;
        ~ScreenRenderer();
        ScreenRenderer& operator = (const ScreenRenderer&) = delete;

        void start(const glm::vec2& size) noexcept;

        void draw_rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture) noexcept;

        void finalize() noexcept;

    private:
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Mesh>   rectangle;
    };
}

#endif
