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

#include <pkzo/GraphicContext.h>

#include "Group.h"
#include "Bounds.h"

namespace pkzo
{
    class SceneRenderer;
    class PhysicsSimulation;

    class Scene;

    template <>
    struct NodeTraits<Scene>
    {
        using Vector = glm::vec3;
        using Matrix = glm::mat4;
        using Bounds = Bounds3;
    };

    using SceneNode  = Node<Scene>;
    using SceneGroup = Group<Scene>;

    struct TestResult
    {
        SceneNode*     node     = nullptr;
        glm::vec3      position = glm::vec3(0.0f);
        glm::vec3      normal   = glm::vec3(0.0f);
    };

    class PKZO_EXPORT Scene : public SceneGroup
    {
    public:
        Scene();

        ~Scene();

        SceneRenderer* get_renderer();
        const SceneRenderer* get_renderer() const;

        PhysicsSimulation* get_physics_simulation();
        const PhysicsSimulation* get_physics_simulation() const;
        void enable_physics_debug();
        void disable_physics_debug();

        void set_gravity(const glm::vec3& value);
        glm::vec3 get_gravity() const;

        std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const;
        std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const;

        void update(float dt) override;

        void draw(pkzo::GraphicContext& gc);

    private:
        std::unique_ptr<SceneRenderer>     renderer;
        std::unique_ptr<PhysicsSimulation> physics_simulation;
    };

    constexpr glm::mat4 position(const glm::vec3& value)
    {
        return glm::translate(glm::mat4(1.0f), value);
    }

    constexpr glm::mat4 position(float x, float y, float z)
    {
        return position(glm::vec3(x, y, z));
    }

    inline glm::mat4 lookat(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return glm::inverse(glm::lookAt(position, target, up));
    }
}
