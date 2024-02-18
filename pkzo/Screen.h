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

#pragma once

#include <glm/glm.hpp>

#include "defines.h"
#include "NodeRoot.h"
#include "InputHandler.h"
#include "ScreenRenderer.h"

namespace pkzo
{
    class Screen;

    template <>
    struct NodeTraits<Screen>
    {
        using Matrix = glm::mat3;
        using Bounds = Bounds<2>;
    };

    class PKZO_EXPORT Screen : public NodeRoot<Screen>, public InputHandler
    {
    public:
        explicit Screen(glm::uvec2 size) noexcept;
        ~Screen() = default;

        glm::uvec2 get_size() const noexcept;
        void resize(glm::uvec2 size) noexcept;

        void set_background_color(glm::vec4 color) noexcept;
        glm::vec4 get_background_color() const noexcept;

        void draw();

        void add_input_handler(InputHandler* handler);
        void remove_input_handler(InputHandler* handler);

        void handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos) override;
        void handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos) override;
        void handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel) override;
        void handle_mouse_wheel(glm::ivec2 rel) override;

        void handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key) override;
        void handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key) override;
        void handle_keboard_text(const std::string_view text) override;

    private:
        glm::uvec2 size;
        glm::vec4  background_color = glm::vec4(0.0f);

        std::vector<InputHandler*> input_handlers;

        std::unique_ptr<ScreenRenderer> renderer;
    };
}
