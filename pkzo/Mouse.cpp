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

#include "EventRouter.h"

namespace pkzo
{
    Mouse::Mouse(EventRouter& er)
    : event_router(er)
    {
        event_router.add_handler(this);
    }

    Mouse::~Mouse()
    {
        event_router.remove_handler(this);
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

    void Mouse::handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos)
    {
        button_press_signal.emit(button, pos);
    }

    void Mouse::handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos)
    {
        button_release_signal.emit(button, pos);
    }

    void Mouse::handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel)
    {
        move_signal.emit(pos, rel);
    }

    void Mouse::handle_mouse_wheel(glm::ivec2 rel)
    {
        wheel_signal.emit(rel);
    }
}
