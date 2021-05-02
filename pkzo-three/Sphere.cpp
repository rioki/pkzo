//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
#include "Sphere.h"

namespace pkzo::three
{
    auto make_sphere(float radius, unsigned int sectors = 32, unsigned int rings = 16)
    {
        auto mesh = std::make_shared<Mesh>();

        auto R = 1.0/(float)(rings-1);
        auto S = 1.0/(float)(sectors-1);

        for(auto r = 0u; r < rings; r++)
        {
            for(auto s = 0u; s < sectors; s++)
            {
                auto x = std::cos(2*PI * s * S) * std::sin(PI * r * R);
                auto y = std::sin(2*PI * s * S) * std::sin(PI * r * R);
                auto z = std::sin(-PI/2.0 + PI * r * R);
                mesh->add_vertex({x * radius, y * radius, z * radius}, {x, y, z}, {s*S, r*R});
            }
        }

        for (auto r = 0u; r < (rings-1); r++)
        {
            for(auto s = 0u; s < (sectors-1); s++)
            {
                auto a = r * sectors + s;
                auto b = r * sectors + (s+1);
                auto c = (r+1) * sectors + (s+1);
                auto d = (r+1) * sectors + s;
                mesh->add_triangle({a, b, c});
                mesh->add_triangle({c, d, a});
            }
        }
        return mesh;
    }

    Sphere::Sphere() noexcept
    : Sphere(glm::mat4(1.0f), 0.5f) {}

    Sphere::Sphere(const glm::mat4& transform, float r) noexcept
    : Geometry(transform), radius(r)
    {
        mesh = make_sphere(radius);
    }

    Sphere::Sphere(const glm::mat4& transform, float r, const std::shared_ptr<Material>& material) noexcept
    : Geometry(transform, material), radius(r)
    {
        mesh = make_sphere(radius);
    }

    float Sphere::get_radius() const noexcept
    {
        return radius;
    }

    std::shared_ptr<Mesh> Sphere::get_mesh() const noexcept
    {
        return mesh;
    }
}
