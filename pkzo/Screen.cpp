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
#include "Screen.h"

#include "Rectangle.h"

namespace pkzo
{
    Screen::Screen(glm::uvec2 s) noexcept
    : size(s)
    {
        background = std::make_unique<Rectangle>();
        background->set_size(glm::vec2(s));
        add_node(*background);
    }

    Screen::~Screen() = default;

    glm::uvec2 Screen::get_size() const noexcept
    {
        return size;
    }

    void Screen::resize(glm::uvec2 s) noexcept
    {
        size = s;
        background->set_size(glm::vec2(s));
    }

    void Screen::set_background_color(glm::vec4 color) noexcept
    {
        background->set_color(color);
    }

    glm::vec4 Screen::get_background_color() const noexcept
    {
        return background->get_color();
    }

    void Screen::draw()
    {
        check(renderer != nullptr);
        renderer->set_size(size);
        renderer->render();
    }

    void Screen::add_input_handler(InputHandler* handler)
    {
        check(handler);
        input_handlers.push_back(handler);
    }

    void Screen::remove_input_handler(InputHandler* handler)
    {
        check(handler);
        auto it = std::ranges::find(input_handlers, handler);
        check(it != input_handlers.end());
        input_handlers.erase(it);
    }

    void Screen::handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_mouse_button_down(button, pos);
        }
    }

    void Screen::handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_mouse_button_up(button, pos);
        }
    }

    void Screen::handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_mouse_move(pos, rel);
        }
    }

    void Screen::handle_mouse_wheel(glm::ivec2 rel)
{
        for (auto handler : input_handlers)
        {
            handler->handle_mouse_wheel(rel);
        }
    }

    void Screen::handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_keboard_down(mod, key);
        }
    }

    void Screen::handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_keboard_up(mod, key);
        }
    }

    void Screen::handle_keboard_text(const std::string_view text)
    {
        for (auto handler : input_handlers)
        {
            handler->handle_keboard_text(text);
        }
    }

    void Screen::activate()
    {
        check(renderer == nullptr);
        renderer = std::make_unique<ScreenRenderer>();

        NodeRoot<Screen>::activate();
    }

    void Screen::deactivate()
    {
        NodeRoot<Screen>::deactivate();

        renderer = nullptr;
    }

    ScreenRenderer* Screen::get_renderer() noexcept
    {
        return renderer.get();
    }
}
