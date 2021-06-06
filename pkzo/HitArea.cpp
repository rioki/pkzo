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

#include "pch.h"
#include "HitArea.h"
#include "physics.h"
#include "Scene.h"
#include "utils.h"

using namespace pkzo::mass_literals;

namespace pkzo
{
    HitArea::HitArea(const glm::vec3& size) noexcept
    : HitArea(glm::mat4(1.0f), size) {}

    HitArea::HitArea(const glm::mat4& transform, const glm::vec3& s) noexcept
    : SceneNode(transform), size(s)
    {}

    HitArea::~HitArea() = default;

    void HitArea::set_size(const glm::vec3& value) noexcept
    {
        size = value;
    }

    const glm::vec3& HitArea::get_size() const noexcept
    {
        return size;
    }

    rsig::signal<glm::vec3, glm::vec3>& HitArea::get_mouse_move_signal() noexcept
    {
        return mouse_move_signal;
    }

    rsig::connection HitArea::on_mouse_move(const std::function<void(glm::vec3, glm::vec3)>& cb) noexcept
    {
        return mouse_move_signal.connect(cb);
    }

    rsig::signal<glm::vec3, MouseButton>& HitArea::get_mouse_down_signal() noexcept
    {
        return mouse_down_signal;
    }

    rsig::connection HitArea::on_mouse_down(const std::function<void (glm::vec3, MouseButton)>& cb) noexcept
    {
        return mouse_down_signal.connect(cb);
    }

    rsig::signal<glm::vec3, MouseButton>& HitArea::get_mouse_up_signal() noexcept
    {
        return mouse_up_signal;
    }

    rsig::connection HitArea::on_mouse_up(const std::function<void (glm::vec3, MouseButton)>& cb) noexcept
    {
        return mouse_up_signal.connect(cb);
    }

    rsig::signal<MouseButton>& HitArea::get_click_signal() noexcept
    {
        return click_signal;
    }

    rsig::connection HitArea::on_click(const std::function<void (MouseButton)>& cb) noexcept
    {
        return click_signal.connect(cb);
    }

    void HitArea::handle_mouse_move(const glm::vec3 pos, const glm::vec3 mov) const noexcept
    {
        mouse_move_signal.emit(pos, mov);
    }

    void HitArea::handle_mouse_down(const glm::vec3 pos, MouseButton button) const noexcept
    {
        mouse_down_signal.emit(pos, button);
        click_armed[to_underlying(button)] = true;
    }

    void HitArea::handle_mouse_up(const glm::vec3 pos, MouseButton button) const noexcept
    {
        mouse_up_signal.emit(pos, button);
        if (click_armed[to_underlying(button)])
        {
            click_signal.emit(button);
            click_armed[to_underlying(button)] = false;
        }
    }

    void HitArea::handle_mouse_up_outside(const glm::vec3 pos, MouseButton button) const noexcept
    {
        mouse_up_signal.emit(pos, button); // REVIEW: add flag for outside?
        click_armed[to_underlying(button)] = false;
    }

    void HitArea::update(std::chrono::milliseconds dt) noexcept
    {
        SceneNode::update(dt);
        //rigid_body->set_transform(get_world_transform());
    }

    void HitArea::on_attach_scene(Scene* scene) noexcept
    {
        SceneNode::on_attach_scene(scene);

        auto physics = scene->get_physics();
        assert(physics);
        physics_ghost = physics->add_box(get_world_transform(), size, 0kg, physics::CollisionGroup::INTERACTION, physics::CollisionGroup::INTERACTION);
        physics_ghost->set_user_data(static_cast<SceneNode*>(this));
    }

    void HitArea::on_detach_scene() noexcept
    {
        if (physics_ghost)
        {
            auto physics = get_scene()->get_physics();
            assert(physics);
            physics->remove_body(physics_ghost);
            physics_ghost = nullptr;
        }

        SceneNode::on_detach_scene();
    }

    /*void HitArea::handle_mouse_button_down(MouseButton button, glm::vec2 pos)
    {
        auto min = position - size / 2.0f;
        auto max = position + size / 2.0f;
        if (pos.x >= min.x && pos.y >= min.y &&
            pos.x <= max.x && pos.y <= max.y)
        {
            click_armed[to_underlying(button)] = true;
            if (mouse_down_cb)
            {
                auto local_pos = pos - position;
                mouse_down_cb(button, local_pos);
            }
        }
    }

    void HitArea::handle_mouse_button_up(MouseButton button, glm::vec2 pos)
    {
        if (click_armed[to_underlying(button)])
        {
            auto min = position - size / 2.0f;
            auto max = position + size / 2.0f;
            if (pos.x >= min.x && pos.y >= min.y &&
                pos.x <= max.x && pos.y <= max.y)
            {
                if (click_cb && button == MouseButton::LEFT)
                {
                    click_cb();
                }
            }

            if (mouse_up_cb)
            {
                auto local_pos = pos - position;
                mouse_up_cb(button, local_pos);
            }
        }
        click_armed[to_underlying(button)] = false;
    }

    void HitArea::handle_mouse_move(glm::vec2 pos, glm::vec2 rel)
    {
        auto min = position - size / 2.0f;
        auto max = position + size / 2.0f;
        if (pos.x >= min.x && pos.y >= min.y &&
            pos.x <= max.x && pos.y <= max.y)
        {
            if (mouse_in == false)
            {
                if (enter_cb)
                {
                    enter_cb();
                }
                mouse_in = true;
            }

            if (mouse_move_cb)
            {
                mouse_move_cb(pos);
            }
        }
        else
        {
            if (mouse_in == true)
            {
                if (leave_cb)
                {
                    leave_cb();
                }
                mouse_in = false;
            }
        }
    }*/
}

