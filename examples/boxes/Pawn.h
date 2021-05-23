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

#include <pkzo/pkzo.h>

namespace boxes
{
    class Pawn : public pkzo::SceneNodeGroup
    {
    public:
        Pawn() noexcept;

        const std::shared_ptr<pkzo::Camera>& get_camera() noexcept;

        void set_fore_key(pkzo::Key value) noexcept;
        pkzo::Key get_fore_key() const noexcept;
        void set_back_key(pkzo::Key value) noexcept;
        pkzo::Key get_back_key() const noexcept;
        void set_left_key(pkzo::Key value) noexcept;
        pkzo::Key get_left_key() const noexcept;
        void set_right_key(pkzo::Key value) noexcept;
        pkzo::Key get_right_key() const noexcept;
        void set_up_key(pkzo::Key value) noexcept;
        pkzo::Key get_up_key() const noexcept;
        void set_down_key(pkzo::Key value) noexcept;
        pkzo::Key get_downt_key() const noexcept;
        void set_mouse_sensitivity(float value) noexcept;
        float get_mouse_sensitivity() const noexcept;
        void set_invert_mouse(float value) noexcept;
        float get_invert_mouse() const noexcept;

        void handle_key_down(pkzo::Key key) noexcept;
        void handle_key_up(pkzo::Key key) noexcept;
        void handle_mouse_move(const glm::vec2& mov) noexcept;
        void handle_mouse_down(pkzo::MouseButton button) noexcept;
        void handle_mouse_up(pkzo::MouseButton button) noexcept;

    protected:
        void update(std::chrono::milliseconds dt) noexcept override;

    private:
        std::shared_ptr<pkzo::Camera> camera;

        float speed      = 10.0f;

        pkzo::Key fore_key          = pkzo::Key::W;
        pkzo::Key back_key          = pkzo::Key::S;
        pkzo::Key left_key          = pkzo::Key::A;
        pkzo::Key right_key         = pkzo::Key::D;
        pkzo::Key up_key            = pkzo::Key::SPACE;
        pkzo::Key down_key          = pkzo::Key::LCTRL;
        float     mouse_sensitivity = 1.0f;
        bool      invert_mouse      = false;

        bool  rotate     = false;
        bool  move_fore  = false;
        bool  move_back  = false;
        bool  move_left  = false;
        bool  move_right = false;
        bool  move_up  = false;
        bool  move_down = false;
        glm::vec2 rotation = {0.0f, 0.0f};
    };
}
