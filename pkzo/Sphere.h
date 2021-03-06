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

#pragma once
#include "config.h"

#include "Geometry.h"

namespace pkzo
{
    //! Sphere
    class PKZO_EXPORT Sphere : public Geometry
    {
    public:
        Sphere() noexcept;
        Sphere(const glm::mat4& transform, float radius) noexcept;
        Sphere(const glm::mat4& transform, float radius, const std::shared_ptr<Material>& material) noexcept;

        float get_radius() const noexcept;

        std::shared_ptr<Mesh> get_mesh() const noexcept override;

    protected:
        std::shared_ptr<physics::RigidBody> create_rigid_body(std::shared_ptr<physics::World>& physics, KiloGramm mass, physics::CollisionGroup group, physics::CollisionGroup mask) noexcept override;

    private:
        float radius = 0.5f;
        std::shared_ptr<Mesh> mesh;
    };
}
