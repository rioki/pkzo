#pragma once
class SdlInputSystem
{
};


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
#include "config.h"

#include <memory>

#include "InputSystem.h"
#include "SdlSentry.h"

namespace pkzo
{
    class SdlMouse;
    class SdlKeyboard;
    class SdlJoystick;

    class ICE_EXPORT SdlInputSystem : public InputSystem
    {
    public:
        SdlInputSystem(Engine& e) noexcept;
        ~SdlInputSystem();

        Mouse* get_mouse() noexcept override;
        const Mouse* get_mouse() const noexcept override;

        Keyboard* get_keyboard() noexcept override;
        const Keyboard* get_keyboard() const noexcept override;

        std::vector<Joystick*> get_joysticks() noexcept override;
        std::vector<const Joystick*> get_joysticks() const noexcept override;

        void inject_mouse_button_down(MouseButton button, glm::ivec2 position) noexcept override;
        void inject_mouse_button_up(MouseButton button, glm::ivec2 position) noexcept override;
        void inject_mouse_move(glm::ivec2 position, glm::ivec2 motion) noexcept override;
        void inject_mouse_wheel(glm::ivec2 motion) noexcept override;

        void inject_key_down(KeyMod mod, Key key) noexcept override;
        void inject_key_up(KeyMod mod, Key key) noexcept override;
        void inject_text(const std::string_view text) noexcept override;

        void tick() override;

    private:
        SdlSentry                                 sdl_sentry;

        std::unique_ptr<SdlMouse>                 mouse;
        std::unique_ptr<SdlKeyboard>              keyboard;
        std::vector<std::unique_ptr<SdlJoystick>> joysticks;
    };
}
