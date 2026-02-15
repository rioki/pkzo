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

#include <pkzo/Texture.h>
#include <pkzo/Mesh.h>

#include "Shape.h"

namespace pkzo2d
{
    class Scene;
    using pkzo::Texture;

    class PKZO2D_EXPORT Rectangle : public Shape
    {
    public:
        struct Specs
        {
            Node*                    parent    = nullptr;
            glm::mat3                transform = glm::mat3(1.0f);
            glm::vec2                size      = glm::vec2(15.0f);
            glm::vec4                color     = glm::vec4(1.0f);
            std::shared_ptr<Texture> texture   = nullptr;
        };

        Rectangle(Specs specs);

        ~Rectangle();

        void set_size(const glm::vec2& value);
        const glm::vec2& get_size() const;
        void set_color(const glm::vec4& value);
        void set_texture(const std::shared_ptr<Texture>& value);

        glm::mat4 get_model_matrix() const override;
        std::shared_ptr<Mesh> get_mesh() const override;
        glm::vec4 get_color() const override;
        std::shared_ptr<Texture> get_texture() const override;

    private:
        glm::vec2                size;
        glm::vec4                color;
        std::shared_ptr<Texture> texture;

        mutable std::shared_ptr<Mesh> mesh;
    };
}
