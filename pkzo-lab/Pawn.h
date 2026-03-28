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

#include <pkzo/pkzo.h>
#include <pkzo3d/pkzo3d.h>

namespace lab
{
    class Pawn : public pkzo3d::Group
    {
    public:
        struct Specs
        {
            pkzo3d::Node*  parent       = nullptr;
            glm::mat4      transform    = glm::mat4(1.0f);
            float          speed        = 2.0f;
            pkzo::ScanCode fore_key     = pkzo::ScanCode::W;
            pkzo::ScanCode back_key     = pkzo::ScanCode::S;
            pkzo::ScanCode left_key     = pkzo::ScanCode::A;
            pkzo::ScanCode right_key    = pkzo::ScanCode::D;
            pkzo::ScanCode up_key       = pkzo::ScanCode::SPACE;
            pkzo::ScanCode down_key     = pkzo::ScanCode::LCTRL;
            float          mouse_accel  = 0.25f;
            bool           invert_mouse = true;

        };

        Pawn(Specs specs);

        void set_move_input(glm::vec3 value);
        void add_move_input(glm::vec3 value);
        glm::vec3 get_move_input() const;

        void set_look_input(glm::vec2 value);
        void add_look_input(glm::vec2 value);
        glm::vec2 get_look_input() const;

        void update(float dt) override;

        void handle_input(const pkzo::InputEvent& event);

    private:
        // settings
        float          speed;
        pkzo::ScanCode fore_key;
        pkzo::ScanCode back_key;
        pkzo::ScanCode left_key;
        pkzo::ScanCode right_key;
        pkzo::ScanCode up_key;
        pkzo::ScanCode down_key;
        float          mouse_accel;
        bool           invert_mouse;

        // state
        glm::vec3 move_input = glm::vec3(0.0f);
        glm::vec2 look_input = glm::vec2(0.0f);
    };
}