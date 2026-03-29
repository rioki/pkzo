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

#include "pch.h"

#include "SphereGeometry.h"

namespace pkzo
{
    std::shared_ptr<Mesh> create_sphere_mesh(float diameter, unsigned int sectors, unsigned int rings)
    {
        auto specs = pkzo::MeshData{};

        auto radius = diameter / 2.0f;

        for (unsigned int r = 0; r <= rings; r++)
        {
            auto v = static_cast<float>(r) / static_cast<float>(rings);
            auto phi = glm::pi<float>() * v;

            for (unsigned int s = 0; s <= sectors; s++)
            {
                auto u = static_cast<float>(s) / static_cast<float>(sectors);
                auto theta = glm::two_pi<float>() * u;

                auto x = std::cos(theta) * std::sin(phi);
                auto y = std::sin(theta) * std::sin(phi);
                auto z = std::cos(phi);

                auto normal = glm::vec3(x, y, z);
                auto tangent = glm::vec3(-std::sin(theta), std::cos(theta), 0.0f);
                auto texcoord = glm::vec2(u, v);

                specs.vertexes.push_back(normal * radius);
                specs.normals.push_back(normal);
                specs.tangents.push_back(tangent);
                specs.texcoords.push_back(texcoord);
            }
        }

        for (unsigned int r = 0; r < rings; r++)
        {
            for (unsigned int s = 0; s < sectors; s++)
            {
                auto i0 = (r + 0) * (sectors + 1) + (s + 0);
                auto i1 = (r + 1) * (sectors + 1) + (s + 0);
                auto i2 = (r + 1) * (sectors + 1) + (s + 1);
                auto i3 = (r + 0) * (sectors + 1) + (s + 1);

                specs.faces.emplace_back(i0, i1, i2);
                specs.faces.emplace_back(i0, i2, i3);
            }
        }

        return Mesh::create(specs);
    }

    SphereGeometry::SphereGeometry(Init init)
    : Geometry({
        .parent     = init.parent,
        .transform  = init.transform,
        .visible    = init.visible,
        .collidable = init.collidable,
        .material   = init.material}),
      diameter(init.diameter),
      sectors(init.sectors),
      rings(init.rings) {}

    SphereGeometry::~SphereGeometry() = default;

    void SphereGeometry::set_diameter(float value)
    {
        diameter = value;
        mesh = nullptr;
    }

    float SphereGeometry::get_diameter() const
    {
        return diameter;
    }

    unsigned int SphereGeometry::get_sectors() const
    {
        return sectors;
    }

    unsigned int SphereGeometry::get_rings() const
    {
        return rings;
    }

    Bounds3 SphereGeometry::get_bounds() const
    {
        auto hs = glm::vec3(diameter / 2.0f);
        return Bounds3(-hs, hs);
    }

    std::shared_ptr<Mesh> SphereGeometry::get_mesh() const
    {
        if (mesh)
        {
            return mesh;
        }

        mesh = create_sphere_mesh(diameter, sectors, rings);
        return mesh;
    }
}
