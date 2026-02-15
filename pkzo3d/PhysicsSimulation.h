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

#include <memory>
#include <optional>

#include <glm/glm.hpp>

#include "api.h"

namespace pkzo3d
{
    class Node;
    class Body;
    class Ghost;
    class Geometry;
    class Renderer;

    struct TestResult
    {
        Node*          node     = nullptr;
        glm::vec3      position = glm::vec3(0.0f);
        glm::vec3      normal   = glm::vec3(0.0f);
    };

    class PKZO3D_EXPORT PhysicsSimulation
    {
    public:
        static std::unique_ptr<PhysicsSimulation> create();

        virtual ~PhysicsSimulation() = default;

        virtual void add(Body* body) = 0;
        virtual void remove(Body* body) = 0;

        virtual void add(Ghost* ghost) = 0;
        virtual void remove(Ghost* ghost) = 0;

        virtual void add(Geometry* geometry) = 0;
        virtual void remove(Geometry* geometry) = 0;

        virtual void set_gravity(const glm::vec3& value) = 0;
        virtual glm::vec3 get_gravity() const = 0;

        virtual std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const = 0;
        virtual std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const = 0;

        virtual void update(float dt) = 0;

        virtual void enable_debug_render(Renderer& renderer) = 0;
        virtual void disable_debug_render() = 0;

    private:

    };
}
