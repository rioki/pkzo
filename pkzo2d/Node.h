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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <rsig/rsig.h>

#include <pkzo/Mouse.h>

#include "api.h"
#include "glm_2d.h"

namespace pkzo2d
{
    class Screen;
    using pkzo::MouseButton;

    class PKZO2D_EXPORT Node
    {
    public:
        struct Specs
        {
            Node*     parent    = nullptr;
            glm::mat4 transform = glm::mat4(1.0f);
        };

        Node(Specs specs);

        virtual ~Node();

        Screen* get_screen();
        const Screen* get_screen() const;

        Node* get_parent();
        const Node* get_parent() const;

        void set_transform(const glm::mat3& value);
        const glm::mat3& get_transform() const;
        glm::mat3 get_global_transform() const;

        rsig::connection on_move(const std::function<void ()>& handler);

        virtual void handle_mouse_button_down(glm::vec2& pos, MouseButton button);
        virtual void handle_mouse_button_up(glm::vec2& pos, MouseButton button);

        virtual void update(float dt);

    private:
        Node*     parent;
        glm::mat3 transform;

        rsig::signal<> move_signal;
        rsig::slot     parent_move_slot;

        Node(const Node&) = delete;
        Node& operator = (const Node&) = delete;
    };

    constexpr glm::mat3 position(const glm::vec2& value)
    {
        return glm::translate(glm::mat3(1.0f), value);
    }

    constexpr glm::mat4 position(float x, float y)
    {
        return position(glm::vec2(x, y));
    }
}
