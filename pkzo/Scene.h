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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "enums.h"
#include "SceneNodeGroup.h"
#include "physics.h"

namespace pkzo
{
    class Camera;
    class Pipeline;
    class Actor;

    struct TestResult
    {
        std::shared_ptr<SceneNode> node;
        glm::vec3 position;
        glm::vec3 normal;
    };

    //! 3D Scene
    class PKZO_EXPORT Scene : public SceneNodeGroup
    {
    public:
        Scene();
        Scene(std::shared_ptr<physics::World> physics);
        ~Scene();

        Pipeline* get_render_pipeline() noexcept;
        const Pipeline* get_render_pipeline() const noexcept;

        void add_node(std::shared_ptr<SceneNode> child) noexcept override;
        void remove_node(std::shared_ptr<SceneNode> child) noexcept override;

        void update(std::chrono::milliseconds dt) noexcept override;
        void draw(const Camera& camera) const noexcept;

        void set_gravity(const glm::vec3& value) noexcept;
        glm::vec3 get_gravity() const noexcept;

        std::shared_ptr<physics::World> get_physics() noexcept;
        std::shared_ptr<const physics::World> get_physics() const noexcept;

        std::optional<TestResult> test_ray(const glm::vec3& start, const glm::vec3& end) const noexcept;
        std::optional<TestResult> test_sphere_sweep(const glm::vec3& start, const glm::vec3& end, float radius) const noexcept;

        void handle_key_press(Key key, KeyMod mod) noexcept;
        void handle_key_release(Key key, KeyMod mod) noexcept;
        void handle_mouse_move(glm::vec2 pos, glm::vec2 rel) noexcept;
        void handle_mouse_press(MouseButton button, glm::vec2 pos) noexcept;
        void handle_mouse_release(MouseButton button, glm::vec2 pos) noexcept;

    private:
        std::unique_ptr<Pipeline> render_pipeline;
        std::shared_ptr<physics::World> physics;

        std::list<Actor*> actors;

        void register_actor(Actor* actor);
        void unregister_actor(Actor* actor);

    friend class Actor;
    };
}