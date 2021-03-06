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

#include <memory>

#include "SceneNode.h"

#include "fwd.h"
#include "Mass.h"
#include "physics.h"

namespace pkzo
{
    //! Geometry
    class PKZO_EXPORT Geometry : public SceneNode
    {
    public:
        Geometry() noexcept;
        Geometry(const glm::mat4& transform) noexcept;
        Geometry(const glm::mat4& transform, const std::shared_ptr<Material>& material) noexcept;

        void set_visible(bool value) noexcept;
        bool get_visible() const noexcept;

        void set_collidable(bool value) noexcept;
        bool get_collidable() const noexcept;

        virtual std::shared_ptr<Mesh> get_mesh() const noexcept = 0;

        void set_material(const std::shared_ptr<Material>& value) noexcept;
        const std::shared_ptr<Material>& get_material() const noexcept;

    protected:
        void on_attach_scene(Scene* scene) noexcept override;
        void on_detach_scene() noexcept override;
        void update(std::chrono::milliseconds dt) noexcept override;

        virtual std::shared_ptr<physics::RigidBody> create_rigid_body(std::shared_ptr<physics::World>& physics, KiloGramm mass, physics::CollisionGroup group, physics::CollisionGroup mask) noexcept = 0;

    private:
        bool visible = true;
        bool collidable = true;

        std::shared_ptr<Material> material = std::make_shared<Material>();

        std::shared_ptr<physics::RigidBody> rigid_body;

        Pipeline*    pipeline        = nullptr;
        unsigned int pipeline_handle = 0;

    friend class Body;
    };
}