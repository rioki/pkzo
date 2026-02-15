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

#include "Rectangle.h"

#include "Screen.h"
#include "Renderer.h"

namespace pkzo2d
{
    std::shared_ptr<Mesh> create_unit_rectangle()
    {
        return Mesh::create({
            .vertexes = {
                {-0.5f,  0.5f, 0.0f},
                { 0.5f,  0.5f, 0.0f},
                { 0.5f, -0.5f, 0.0f},
                {-0.5f, -0.5f, 0.0f}
            },
            .texcoords = {
                {0.0f, 1.0f},
                {1.0f, 1.0f},
                {1.0f, 0.0f},
                {0.0f, 0.0f}
            },
            .faces = {
                {0, 1, 2},
                {2, 3, 0}
            }
        });
    }

    Rectangle::Rectangle(Specs specs)
    : Shape({specs.parent, specs.transform}),
      size(specs.size),
      color(specs.color),
      texture(specs.texture)
    {
        auto renderer = get_screen()->get_renderer();
        renderer->add(this);
    }

    Rectangle::~Rectangle()
    {
        auto renderer = get_screen()->get_renderer();
        renderer->remove(this);
    }

    void Rectangle::set_size(const glm::vec2& value)
    {
        size = value;
    }

    const glm::vec2& Rectangle::get_size() const
    {
        return size;
    }

    void Rectangle::set_color(const glm::vec4& value)
    {
        color = value;
    }

    void Rectangle::set_texture(const std::shared_ptr<Texture>& value)
    {
        texture = value;
    }

    glm::mat4 Rectangle::get_model_matrix() const
    {
        auto mm = Shape::get_model_matrix();
        return glm::scale(mm, glm::vec3(size, 1.0f));
    }

    std::shared_ptr<Mesh> Rectangle::get_mesh() const
    {
        static auto cache = std::weak_ptr<Mesh>{};

        if (mesh)
        {
            return mesh;
        }

        mesh = cache.lock();
        if (mesh)
        {
            return mesh;
        }

        mesh = create_unit_rectangle();
        cache = mesh;
        return mesh;
    }

    glm::vec4 Rectangle::get_color() const
    {
        return color;
    }

    std::shared_ptr<Texture> Rectangle::get_texture() const
    {
        return texture;
    }
}
