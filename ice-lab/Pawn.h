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

#pragma once

#include <ice/ice.h>

namespace lab
{
    class Pawn : public ice::SceneNodeGroup
    {
    public:
        Pawn(const glm::mat4& transform);

        void activate() override;
        void deactivate() override;

    private:
        ice::Camera  camera;

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

        ice::Key fore_key  = ice::Key::W;
        ice::Key back_key  = ice::Key::S;
        ice::Key left_key  = ice::Key::A;
        ice::Key right_key = ice::Key::D;
        ice::Key up_key    = ice::Key::SPACE;
        ice::Key down_key  = ice::Key::LCTRL;
    };
}
