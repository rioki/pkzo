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
#include "Box.h"

#include "Mesh.h"
#include "physics.h"

namespace pkzo
{
    auto make_box(const glm::vec3& size)
    {
        auto mesh = std::make_shared<Mesh>();

        auto hs = size / 2.0f;

        // x pos
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f});
        // x neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, {-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f});
        // y pos
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  0.0f});
        // y neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 0.0f, -1.0f,  0.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, { 0.0f, -1.0f,  0.0f}, { 0.0f,  0.0f});
        // z pos
        mesh->add_vertex({-hs.x, -hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y,  hs.z}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f});
        // z neg
        mesh->add_vertex({-hs.x, -hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 1.0f,  0.0f});
        mesh->add_vertex({ hs.x, -hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f});
        mesh->add_vertex({ hs.x,  hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  1.0f});
        mesh->add_vertex({-hs.x,  hs.y, -hs.z}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f});

        // x pos
        mesh->add_triangle({ 0,  1,  2});
        mesh->add_triangle({ 0,  2,  3});
        // x neg
        mesh->add_triangle({ 6,  5,  4});
        mesh->add_triangle({ 7,  4,  6});
        // y pos
        mesh->add_triangle({ 8,  9, 10});
        mesh->add_triangle({ 8, 10, 11});
        // y neg
        mesh->add_triangle({14, 13, 12});
        mesh->add_triangle({15, 12, 14});
        // z pos
        mesh->add_triangle({16, 17, 18});
        mesh->add_triangle({16, 18, 19});
        // z neg
        mesh->add_triangle({22, 21, 20});
        mesh->add_triangle({23, 20, 22});

        return mesh;
    }

    Box::Box() noexcept
    : Box(glm::mat4(1.0f), glm::vec3(1.0f)) {}

    Box::Box(const glm::mat4& transform, const glm::vec3& s) noexcept
    : Geometry(transform), size(s)
    {
        mesh = make_box(size);
    }

    Box::Box(const glm::mat4& transform, const glm::vec3& s, const std::shared_ptr<Material>& material) noexcept
    : Geometry(transform, material), size(s)
    {
        mesh = make_box(size);
    }

    const glm::vec3& Box::get_size() const noexcept
    {
        return size;
    }

    std::shared_ptr<Mesh> Box::get_mesh() const noexcept
    {
        return mesh;
    }

    std::shared_ptr<physics::RigidBody> Box::create_rigid_body(std::shared_ptr<physics::World>& physics, KiloGramm mass) noexcept
    {
        return physics->add_box(get_world_transform(), size, mass);
    }
}
