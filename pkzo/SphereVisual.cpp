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
#include "SphereVisual.h"

#include "Mesh.h"

namespace pkzo
{
    SphereVisual::SphereVisual()
    : SphereVisual(glm::mat4(1.0f), 1.0f, Visual::get_default_material()) {}

    SphereVisual::SphereVisual(const glm::mat4& transform, const float radius, const std::shared_ptr<const Material>& material) noexcept
    : Visual(transform, get_sphere_mesh(), material, glm::vec3(radius)) {}

    float SphereVisual::get_radius() const noexcept
    {
        return get_local_scale().x;
    }

    void SphereVisual::set_radius(const float value) noexcept
    {
        set_local_scale(glm::vec3(value));
    }

    std::shared_ptr<Mesh> SphereVisual::get_sphere_mesh() noexcept
    {
        static auto cache = std::weak_ptr<Mesh>();

        auto mesh = cache.lock();
        if (mesh)
        {
            return mesh;
        }

        mesh = make_sphere_mesh(1.0f);
        cache = mesh;
        return mesh;
    }
}
