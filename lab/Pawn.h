// pkzo
// Copyright 2022-2023 Sean Farrell
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

#pragma once

#include <pkzo/pkzo.h>

namespace lab
{
    class Pawn : public pkzo::SceneNodeGroup
    {
    public:
        Pawn(const glm::mat4& transform);

        void activate() override;
        void deactivate() override;

    private:
        pkzo::Camera  camera;

        rsig::connection mouse_button_down_con;
        rsig::connection mouse_button_up_con;
        rsig::connection mouse_move_con;
        rsig::connection key_down_con;
        rsig::connection key_up_con;
        rsig::connection tick_con;

        std::chrono::steady_clock::time_point last_tick;

        bool      rotating         = false;
        glm::vec2 cam_uv           = {0.0f, 0.0f};
        bool      invert_mouse     = false;
        float     mouse_senitivity = 0.1f;
        float     speed            = 10.0f;

        bool move_fore  = false;
        bool move_back  = false;
        bool move_left  = false;
        bool move_right = false;
        bool move_up    = false;
        bool move_down  = false;

        pkzo::Key fore_key  = pkzo::Key::W;
        pkzo::Key back_key  = pkzo::Key::S;
        pkzo::Key left_key  = pkzo::Key::A;
        pkzo::Key right_key = pkzo::Key::D;
        pkzo::Key up_key    = pkzo::Key::SPACE;
        pkzo::Key down_key  = pkzo::Key::LCTRL;
        pkzo::Key exit_key  = pkzo::Key::ESCAPE;

        void place_box();
    };
}