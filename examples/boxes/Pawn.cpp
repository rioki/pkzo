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
#include "Pawn.h"

namespace boxes
{
    using fsec = std::chrono::duration<float>;

    Pawn::Pawn() noexcept
    {
        camera = std::make_shared<pkzo::PerspectiveCamera>(pkzo::lookat(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f)));
        add_node(camera);
    }

    const std::shared_ptr<pkzo::Camera>& Pawn::get_camera() noexcept
    {
        return camera;
    }

    void Pawn::set_fore_key(pkzo::Key value) noexcept
    {
        fore_key = value;
    }

    pkzo::Key Pawn::get_fore_key() const noexcept
    {
        return fore_key;
    }

    void Pawn::set_back_key(pkzo::Key value) noexcept
    {
        back_key = value;
    }

    pkzo::Key Pawn::get_back_key() const noexcept
    {
        return back_key;
    }

    void Pawn::set_left_key(pkzo::Key value) noexcept
    {
        left_key = value;
    }

    pkzo::Key Pawn::get_left_key() const noexcept
    {
        return left_key;
    }

    void Pawn::set_right_key(pkzo::Key value) noexcept
    {
        right_key = value;
    }

    pkzo::Key Pawn::get_right_key() const noexcept
    {
        return right_key;
    }

    void Pawn::set_up_key(pkzo::Key value) noexcept
    {
        up_key = value;
    }

    pkzo::Key Pawn::get_up_key() const noexcept
    {
        return up_key;
    }

    void Pawn::set_down_key(pkzo::Key value) noexcept
    {
        down_key = value;
    }

    pkzo::Key Pawn::get_downt_key() const noexcept
    {
        return down_key;
    }

    void Pawn::set_mouse_sensitivity(float value) noexcept
    {
        mouse_sensitivity = value;
    }

    float Pawn::get_mouse_sensitivity() const noexcept
    {
        return mouse_sensitivity;
    }

    void Pawn::set_invert_mouse(float value) noexcept
    {
        invert_mouse = value;
    }

    float Pawn::get_invert_mouse() const noexcept
    {
        return invert_mouse;
    }

    void Pawn::handle_key_down(pkzo::Key key) noexcept
    {
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
    }

    void Pawn::handle_key_up(pkzo::Key key) noexcept
    {
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
    }

    void Pawn::handle_mouse_move(const glm::vec2& mov) noexcept
    {
        if (rotate)
        {
            rotation.x -= mov.x * mouse_sensitivity;
            if (invert_mouse)
            {
                rotation.y += mov.y * mouse_sensitivity;
            }
            else
            {
                rotation.y -= mov.y * mouse_sensitivity;
            }

            auto camera_transform = pkzo::lookat(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
            camera_transform = glm::rotate(camera_transform, glm::radians(rotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
            camera_transform = glm::rotate(camera_transform, glm::radians(rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));
            camera->set_transform(camera_transform);
        }
    }

    void Pawn::handle_mouse_down(pkzo::MouseButton button) noexcept
    {
        if (button == pkzo::MouseButton::MIDDLE)
        {
            rotate = true;
        }
    }

    void Pawn::handle_mouse_up(pkzo::MouseButton button) noexcept
    {
        if (button == pkzo::MouseButton::MIDDLE)
        {
            rotate = false;
        }
    }

    void Pawn::update(std::chrono::milliseconds dt) noexcept
    {
        // ds is defined in camera space, because it will be
        // multiplied by the camera transform.
        // This is not a consession the "Y is up" cult.
        auto ds = glm::vec3(0.0f);
        bool moved = false;
        if (move_fore)
        {
            ds += glm::vec3(0.0f, 0.0f, -1.0f);
            moved = true;
        }
        if (move_back)
        {
            ds += glm::vec3(0.0f, 0.0f, 1.0f);
            moved = true;
        }
        if (move_left)
        {
            ds += glm::vec3(-1.0f, 0.0f, 0.0f);
            moved = true;
        }
        if (move_right)
        {
            ds += glm::vec3(1.0f, 0.0f, 0.0f);
            moved = true;
        }
        if (move_up)
        {
            ds += glm::vec3(0.0f, 1.0f, 0.0f);
            moved = true;
        }
        if (move_down)
        {
            ds += glm::vec3(0.0f, -1.0f, 0.0f);
            moved = true;
        }

        if (moved)
        {
            float dts = std::chrono::duration_cast<fsec>(dt).count();

            auto ct = camera->get_transform();
            ds = glm::vec3(ct * glm::vec4(glm::normalize(ds) * speed * dts, 0.0f));

            auto t = get_transform();
            t = glm::translate(t, ds);
            set_transform(t);
        }

        SceneNodeGroup::update(dt);
    }
}
