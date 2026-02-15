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

#include "CylinderGeometry.h"

#include <numbers>

namespace pkzo3d
{
    std::shared_ptr<Mesh> create_cylinder_mesh(float diameter, float height, unsigned int sectors)
    {
        using std::sin;
        using std::cos;
        using namespace glm;

        constexpr auto PI = static_cast<float>(std::numbers::pi);

        auto specs = pkzo::MeshData{};

        float        radius    = diameter / 2.0f;
        float        rad_step  = 2.0f * PI / (float)sectors;
        float        rad_curve = 2.0f * PI / (float)sectors;

        auto segment_ratio = 1.0/static_cast<float>(sectors-1);
        /*auto cap_circumference = 2.0f * PI * radius;
        auto half_circumference = 0.5 * cap_circumference + height - 2.0f * radius;
        auto cap_ratio  = (0.25f * cap_circumference) / half_circumference;
        auto body_ratio = 1.0f - 2.0f * cap_ratio;
        auto cap_step = (2.0f * cap_ratio) / static_cast<float>((curve*2)-1);*/

        // body
        float zb = height / 2.0f;

        // no deduplication, becuase the texture cords should wrap
        for (auto i = 0u; i <= sectors; i++)
        {
            float u = i * rad_step;

            float x = sin(u) * radius;
            float y = cos(u) * radius;

            auto v1 = vec3(x, y,  zb);
            auto v2 = vec3(x, y, -zb);
            auto n  = normalize(vec3(x, y, 0));
            auto t  = cross(n, vec3(i*segment_ratio, 0, 1));
            auto tc1 = vec2(i*segment_ratio, 0.0f);
            auto tc2 = vec2(i*segment_ratio, 1.0f);

            specs.vertexes.push_back(v1);
            specs.vertexes.push_back(v2);

            specs.normals.push_back(n);
            specs.normals.push_back(n);

            specs.tangents.push_back(t);
            specs.tangents.push_back(t);

            specs.texcoords.push_back(tc1);
            specs.texcoords.push_back(tc2);
        }

        unsigned int base_index = 0;
        for (auto i = 0u; i < sectors; i++)
        {
            // a  c
            // b  d

            auto a = base_index + 2 * i;
            auto b = a + 1;
            auto c = a + 2;
            auto d = a + 3;

            specs.faces.push_back({a, c, b});
            specs.faces.push_back({c, b, d});
        }

        // top cap
        auto v  = vec3(0.0f, 0.0f, zb);
        auto n  = vec3(0.0f, 0.0f, 1.0f);
        auto t  = vec3(0.0f, 1.0f, 0.0f);
        auto tc = vec2(0.5f, 0.5f);

        auto a = specs.vertexes.size();
        specs.vertexes.push_back(v);
        specs.normals.push_back(n);
        specs.tangents.push_back(t);
        specs.texcoords.push_back(tc);

        for (auto i = 0u; i <= sectors; i++)
        {
            auto u = i * rad_step;

            auto x = sin(u);
            auto y = cos(u);

            v  = vec3(x * radius, y * radius,  zb);
            tc = vec2((x + 1.0f) / 2.0f, (y + 1.0f) / 2.0f);

            specs.vertexes.push_back(v);
            specs.normals.push_back(n);
            specs.tangents.push_back(t);
            specs.texcoords.push_back(tc);
        }

        for (auto i = 0u; i <= sectors; i++)
        {
            auto b = a + i;
            auto c = b + 1;

            specs.faces.push_back({a, c, b});
        }

        // low cap
        // CHECKME the tc is like the top cap... it probably should be revered
        v  = vec3(0.0f, 0.0f, -zb);
        n  = vec3(0.0f, 0.0f, -1.0f);
        t  = vec3(0.0f, -1.0f, 0.0f);
        tc = vec2(0.5f, 0.5f);

        a = specs.vertexes.size();
        specs.vertexes.push_back(v);
        specs.normals.push_back(n);
        specs.tangents.push_back(t);
        specs.texcoords.push_back(tc);

        for (auto i = 0u; i <= sectors; i++)
        {
            auto u = i * rad_step;

            auto x = sin(u);
            auto y = cos(u);

            v  = vec3(x * radius, y * radius, -zb);
            tc = vec2((x + 1.0f) / 2.0f, (y + 1.0f) / 2.0f);

            specs.vertexes.push_back(v);
            specs.normals.push_back(n);
            specs.tangents.push_back(t);
            specs.texcoords.push_back(tc);
        }

        for (auto i = 0u; i <= sectors; i++)
        {
            auto b = a + i;
            auto c = b + 1;

            specs.faces.push_back({a, c, b});
        }

        return Mesh::create(specs);
    }

    CylinderGeometry::CylinderGeometry(Specs specs)
    : Geometry({
        .parent     = specs.parent,
        .transform  = specs.transform,
        .visible    = specs.visible,
        .collidable = specs.collidable,
        .material   = specs.material}),
      diameter(specs.diameter),
      height(specs.height),
      sectors(specs.sectors) {}

    CylinderGeometry::~CylinderGeometry() = default;

    float CylinderGeometry::get_diameter() const
    {
        return diameter;
    }
    void CylinderGeometry::set_diameter(float value)
    {
        diameter = value;
        mesh = nullptr;
    }

    float CylinderGeometry::get_height() const
    {
        return height;
    }

    void CylinderGeometry::set_height(float value)
    {
        height = value;
        mesh = nullptr;
    }

    unsigned int CylinderGeometry::get_sectors() const
    {
        return sectors;
    }

    Bounds CylinderGeometry::get_bounds() const
    {
        auto r = diameter / 2.0f;
        auto hs = glm::vec3(r, r, height / 2.0f);
        return Bounds(-hs, hs);
    }

    std::shared_ptr<Mesh> CylinderGeometry::get_mesh() const
    {
        if (mesh)
        {
            return mesh;
        }

        mesh = create_cylinder_mesh(diameter, height, sectors);
        return mesh;
    }
}
