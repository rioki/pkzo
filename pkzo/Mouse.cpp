// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Mouse.h"

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, MouseButton button)
    {
        switch (button)
        {
            case MouseButton::LEFT:
                os << "LEFT";
                break;
            case MouseButton::MIDDLE:
                os << "MIDDLE";
                break;
            case MouseButton::RIGHT:
                os << "RIGHT";
                break;
            case MouseButton::BUTTON4:
                os << "BUTTON4";
                break;
            case MouseButton::BUTTON5:
                os << "BUTTON5";
                break;
            default:
                os << "MouseButton(0x" << std::hex << static_cast<unsigned int>(button) << ")";
        }
        return os;
    }

    Mouse::Mouse(EventRouter& er)
    : event_router(er)
    {
        event_conn = event_router.on_event(rex::mem_fun(this, &Mouse::handle_event));
    }

    Mouse::~Mouse()
    {
        event_router.get_event_signal().disconnect(event_conn);
    }

    bool Mouse::is_pressed(MouseButton button) const noexcept
    {
        auto btn = SDL_BUTTON(static_cast<unsigned int>(button));
        return (SDL_GetMouseState(nullptr, nullptr) & btn) == btn;
    }

    void Mouse::set_cursor_visible(bool value) noexcept
    {
        SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
    }

    bool Mouse::get_cursor_visible() const noexcept
    {
        return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    }

    glm::ivec2 Mouse::get_cursor_position() const noexcept
    {
        glm::ivec2 pos;
        SDL_GetMouseState(&pos.x, &pos.y);
        return pos;
    }

    rex::connection Mouse::on_button_press(const std::function<void (MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_press_signal.connect(cb);
    }

    rex::signal<MouseButton, glm::ivec2>& Mouse::get_button_press_signal() noexcept
    {
        return button_press_signal;
    }

    rex::connection Mouse::on_button_release(const std::function<void (MouseButton, glm::ivec2)>& cb) noexcept
    {
        return button_release_signal.connect(cb);
    }

    rex::signal<MouseButton, glm::ivec2>& Mouse::get_button_release_signal() noexcept
    {
        return button_release_signal;
    }

    rex::connection Mouse::on_move(const std::function<void (glm::ivec2, glm::ivec2)>& cb) noexcept
    {
        return move_signal.connect(cb);
    }

    rex::signal<glm::ivec2, glm::ivec2>& Mouse::get_move_signal() noexcept
    {
        return move_signal;
    }

    rex::connection Mouse::on_wheel(const std::function<void (glm::ivec2)>& cb) noexcept
    {
        return wheel_signal.connect(cb);
    }

    rex::signal<glm::ivec2>& Mouse::get_wheel_signal() noexcept
    {
        return wheel_signal;
    }

    void Mouse::handle_event(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                button_press_signal.emit(static_cast<MouseButton>(event.button.button), glm::ivec2(event.button.x, event.button.y));
                break;
            case SDL_MOUSEBUTTONUP:
                button_release_signal.emit(static_cast<MouseButton>(event.button.button), glm::ivec2(event.button.x, event.button.y));
                break;
            case SDL_MOUSEMOTION:
                move_signal.emit(glm::ivec2(event.motion.x, event.motion.y), glm::ivec2(event.motion.xrel, event.motion.yrel));
                break;
            case SDL_MOUSEWHEEL:
                wheel_signal.emit(glm::ivec2(event.wheel.x, event.wheel.y));
                break;
        }
    }
}
