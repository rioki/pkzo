// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "Pawn.h"

namespace lab
{
    using fsec = std::chrono::duration<float>;

    auto camera_x_forward()
    {
        static auto cache = ice::lookat(glm::vec3(0.0f), glm::vec3(1.0f, 0.0, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        return cache;
    }

    auto safe_resolution(ice::Engine& engine)
    {
        auto window = engine.get_window();
        assert(window);
        return window->get_size();
    }

    Pawn::Pawn(const glm::mat4& transform)
    : ice::SceneNodeGroup(transform)
    {
        camera.set_transform(camera_x_forward());
        add_node(camera);
    }

    void Pawn::activate()
    {
        auto* engine = get_engine();
        assert(engine);

        mouse_senitivity = engine->get_setting("Pawn", "mouse_senitivity", mouse_senitivity);
        invert_mouse     = engine->get_setting("Pawn", "invert_mouse",     invert_mouse);
        fore_key         = engine->get_setting("Pawn", "fore_key",         fore_key);
        down_key         = engine->get_setting("Pawn", "down_key",         down_key);
        left_key         = engine->get_setting("Pawn", "left_key",         left_key);
        right_key        = engine->get_setting("Pawn", "down_key",         right_key);
        up_key           = engine->get_setting("Pawn", "up_key",           up_key);
        down_key         = engine->get_setting("Pawn", "down_key",         down_key);

        camera.set_fov(engine->get_setting("Pawn", "fov", 90.0f));
        camera.set_resolution(safe_resolution(*engine));

        ice::SceneNodeGroup::activate();

        last_tick = std::chrono::steady_clock::now();

        auto* mouse = engine->get_mouse();
        assert(mouse);
        mouse_button_down_con = mouse->on_button_down([this] (auto button, auto pos) {
            if (button == ice::MouseButton::MIDDLE)
            {
                rotating = true;
            }
        });
        mouse_button_up_con = mouse->on_button_up([this] (auto button, auto pos) {
            if (button == ice::MouseButton::MIDDLE)
            {
                rotating = false;
            }
        });
        mouse_move_con = mouse->on_move([this] (auto pos, auto rel) {
            if (rotating)
            {
                auto duv = glm::vec2(-rel) * mouse_senitivity;
                if (invert_mouse)
                {
                    duv.y = -duv.y;
                }
                cam_uv += duv;
                auto t = camera_x_forward();
                // axis in camera space (-z is forward)
                t = glm::rotate(t, glm::radians(cam_uv.x), glm::vec3(0.0f, 1.0f, 0.0f));
                t = glm::rotate(t, glm::radians(cam_uv.y), glm::vec3(1.0f, 0.0f, 0.0f));
                camera.set_transform(t);
            }
        });

        auto* keyboard = engine->get_keyboard();
        assert(keyboard);
        key_down_con = keyboard->on_key_down([this] (auto /*mod*/, auto key) {
            if (key == fore_key)
            {
                move_fore = true;
            }
            if (key == back_key)
            {
                move_back = true;
            }
            if (key == left_key)
            {
                move_left = true;
            }
            if (key == right_key)
            {
                move_right = true;
            }
            if (key == up_key)
            {
                move_up = true;
            }
            if (key == down_key)
            {
                move_down = true;
            }
        });
        key_up_con = keyboard->on_key_up([this] (auto /*mod*/, auto key) {
            if (key == fore_key)
            {
                move_fore = false;
            }
            if (key == back_key)
            {
                move_back = false;
            }
            if (key == left_key)
            {
                move_left = false;
            }
            if (key == right_key)
            {
                move_right = false;
            }
            if (key == up_key)
            {
                move_up = false;
            }
            if (key == down_key)
            {
                move_down = false;
            }
        });

        tick_con = engine->on_tick([this] () {
            // TODO dt, from engine?
            auto now = std::chrono::steady_clock::now();
            auto dt  = fsec(now - last_tick).count();
            last_tick = now;

            // axis in camera space (-z is forward)
            auto move_this_frame = false;
            auto move_dir = glm::vec3(0.0f);
            if (move_fore)
            {
                move_dir += glm::vec3(0.0f, 0.0f, -1.0f);
                move_this_frame = true;
            }
            if (move_back)
            {
                move_dir += glm::vec3(0.0f, 0.0f, 1.0f);
                move_this_frame = true;
            }
            if (move_left)
            {
                move_dir += glm::vec3(-1.0f, 0.0f, 0.0f);
                move_this_frame = true;
            }
            if (move_right)
            {
                move_dir += glm::vec3(1.0f, 0.0f, 0.0f);
                move_this_frame = true;
            }
            if (move_up)
            {
                move_dir += glm::vec3(0.0f, 1.0f, 0.0f);
                move_this_frame = true;
            }
            if (move_down)
            {
                move_dir += glm::vec3(0.0f, -1.0f, 0.0f);
                move_this_frame = true;
            }

            if (move_this_frame == false)
            {
                return;
            }

            auto look_matrix = camera.get_transform();
            auto ds = glm::transform(look_matrix, glm::normalize(move_dir) * speed * dt);

            auto transform = get_transform();
            transform = glm::translate(transform, ds);
            set_transform(transform);
        });
    }

    void Pawn::deactivate()
    {
        auto* engine = get_engine();
        assert(engine);
        auto* mouse = engine->get_mouse();
        assert(mouse);
        auto* keyboard = engine->get_keyboard();
        assert(keyboard);

        engine->get_tick_signal().disconnect(tick_con);
        mouse->get_button_down_signal().disconnect(mouse_button_down_con);
        mouse->get_button_up_signal().disconnect(mouse_button_up_con);
        mouse->get_move_signal().disconnect(mouse_move_con);
        keyboard->get_key_down_signal().disconnect(key_down_con);
        keyboard->get_key_up_signal().disconnect(key_up_con);

        ice::SceneNodeGroup::deactivate();
    }
}
