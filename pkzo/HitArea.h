//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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

#include <functional>

#include "fwd.h"
#include "enums.h"
#include "rsig.h"
#include "SceneNode.h"

namespace pkzo
{
    //! Interaction Hot Zone
    class PKZO_EXPORT HitArea : public SceneNode
    {
    public:
        HitArea(const glm::vec3& size) noexcept;
        HitArea(const glm::mat4& transform, const glm::vec3& size) noexcept;
        ~HitArea();

        void set_size(const glm::vec3& value) noexcept;
        const glm::vec3& get_size() const noexcept;

        rsig::signal<glm::vec3, glm::vec3>& get_mouse_move_signal() noexcept;
        rsig::connection on_mouse_move(const std::function<void (glm::vec3, glm::vec3)>& cb) noexcept;

        rsig::signal<glm::vec3, MouseButton>& get_mouse_down_signal() noexcept;
        rsig::connection on_mouse_down(const std::function<void (glm::vec3, MouseButton)>& cb) noexcept;

        rsig::signal<glm::vec3, MouseButton>& get_mouse_up_signal() noexcept;
        rsig::connection on_mouse_up(const std::function<void (glm::vec3, MouseButton)>& cb) noexcept;

        rsig::signal<MouseButton>& get_click_signal() noexcept;
        rsig::connection on_click(const std::function<void (MouseButton)>& cb) noexcept;

        void handle_mouse_move(const glm::vec3 pos, const glm::vec3 mov) const noexcept;
        void handle_mouse_down(const glm::vec3 pos, MouseButton button) const noexcept;
        void handle_mouse_up(const glm::vec3 pos, MouseButton button) const noexcept;
        void handle_mouse_up_outside(const glm::vec3 pos, MouseButton button) const noexcept;

    protected:
        void on_attach_scene(Scene* scene) noexcept override;
        void on_detach_scene() noexcept override;
        void update(std::chrono::milliseconds dt) noexcept override;

    private:
        glm::vec3 size = glm::vec3(1.0f);

        rsig::signal<glm::vec3, glm::vec3>   mouse_move_signal;
        rsig::signal<glm::vec3, MouseButton> mouse_down_signal;
        rsig::signal<glm::vec3, MouseButton> mouse_up_signal;
        rsig::signal<MouseButton>            click_signal;

        mutable bool click_armed[5] = {false};

        std::shared_ptr<physics::RigidBody> physics_ghost;
    };
}
