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
#include "config.h"

#include <vector>
#include <string_view>

#include <glm/glm.hpp>

#include "System.h"

namespace ice
{
    class Mouse;
    class Keyboard;
    class Joystick;

    enum class MouseButton;
    enum class KeyMod;
    enum class Key;

    class ICE_EXPORT InputSystem : public System
    {
    public:
        InputSystem(Engine& e) noexcept
        : System(e) {}

        virtual ~InputSystem() = default;

        virtual Mouse* get_mouse() noexcept = 0;
        virtual const Mouse* get_mouse() const noexcept = 0;

        virtual Keyboard* get_keyboard() noexcept = 0;
        virtual const Keyboard* get_keyboard() const noexcept = 0;

        virtual std::vector<Joystick*> get_joysticks() noexcept = 0;
        virtual std::vector<const Joystick*> get_joysticks() const noexcept = 0;

        virtual void inject_mouse_button_down(MouseButton button, glm::ivec2 position) noexcept = 0;
        virtual void inject_mouse_button_up(MouseButton button, glm::ivec2 position) noexcept = 0;
        virtual void inject_mouse_move(glm::ivec2 position, glm::ivec2 motion) noexcept = 0;
        virtual void inject_mouse_wheel(glm::ivec2 motion) noexcept = 0;

        virtual void inject_key_down(KeyMod mod, Key key) noexcept = 0;
        virtual void inject_key_up(KeyMod mod, Key key) noexcept = 0;
        virtual void inject_text(const std::string_view text) noexcept = 0;
    };
}
