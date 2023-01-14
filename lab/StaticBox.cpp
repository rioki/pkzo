// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"
#include "StaticBox.h"

namespace lab
{
    StaticBox::StaticBox(const glm::mat4& transform, const glm::vec3& size, const std::shared_ptr<const pkzo::Material>& material)
    : pkzo::SceneNodeGroup(transform),
      visual{glm::mat4(1.0f), size, material}
    {
        add_node(visual);
    }

    void StaticBox::set_size(const glm::vec3& value) noexcept
    {
        visual.set_size(value);
    }

    const glm::vec3& StaticBox::get_size() const noexcept
    {
        return visual.get_size();
    }

    void StaticBox::set_material(const std::shared_ptr<const pkzo::Material>& value) noexcept
    {
        visual.set_material(value);
    }

    const std::shared_ptr<const pkzo::Material>& StaticBox::get_material() const noexcept
    {
        return visual.get_material();
    }
}
