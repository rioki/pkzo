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

#include "Pawn.h"

#include <pkzo/debug.h>

namespace lab
{
    using pkzo::check;
    using pkzo::trace;

    Pawn::Pawn(Specs specs)
    : Group(std::move(specs))
    {
        add<pkzo3d::Camera>({
             .transform = pkzo3d::lookat(glm::vec3(0.0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
        });
    }

    void Pawn::set_move_input(glm::vec3 value)
    {
        move_input = value;
    }

    void Pawn::add_move_input(glm::vec3 value)
    {
        move_input += value;
    }

    glm::vec3 Pawn::get_move_input() const
    {
        return move_input;
    }

    void Pawn::set_look_input(glm::vec2 value)
    {
        look_input = value;
    }

    void Pawn::add_look_input(glm::vec2 value)
    {
        look_input += value;
    }

    glm::vec2 Pawn::get_look_input() const
    {
        return look_input;
    }

    void Pawn::update(float dt)
    {
        auto t = get_transform();

        auto rot = glm::mat3(t);
        auto pos = glm::vec3(t[3]);

        look_input.y = glm::clamp(look_input.y, -85.0f, 85.0f);

        constexpr auto up   = glm::vec3(0.0f, 0.0f, 1.0f);
        constexpr auto left = glm::vec3(0.0f, 1.0f, 0.0f);

        auto new_t = glm::mat4(1.0f);
        new_t = glm::rotate(new_t, glm::radians(look_input.x), up);
        new_t = glm::rotate(new_t, glm::radians(look_input.y), left);

        pos += rot * (move_input * speed * dt);

        new_t[3] = glm::vec4(pos, 1.0);
        set_transform(new_t);
    }
}