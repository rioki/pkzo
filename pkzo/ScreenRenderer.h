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

#pragma once

#include <stack>

#include <glm/glm.hpp>
#include <glow/glow.h>

#include <rex/cache.h>

#include "defines.h"
#include "Image.h"

namespace pkzo
{
    class PKZO_EXPORT ScreenRenderer
    {
    public:
        ScreenRenderer();
        ~ScreenRenderer();

        void set_size(glm::uvec2 value);
        glm::uvec2 get_size() const;

        unsigned int add_rectangle(const glm::mat3& transform, glm::vec2 size, glm::vec4 color);
        unsigned int add_rectangle(const glm::mat3& transform, glm::vec2 size, glm::vec4 color, const Image& image);
        void remove_rectangle(unsigned int id);

        void render();

    private:
        struct Geometry
        {
            glm::mat3                      transform;
            glm::vec2                      size;
            glm::vec4                      color;
            std::shared_ptr<glow::Texture> texture;
        };

        glow::Shader          shader;
        glow::VertexBuffer    rectangle;

        glm::uvec2 size;

        unsigned int next_id = 0;
        std::map<unsigned int, Geometry> geometries;

        rex::cache<Image, std::shared_ptr<glow::Texture>> texture_cache;
    };
}
