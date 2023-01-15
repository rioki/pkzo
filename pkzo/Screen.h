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

#include <glm/glm.hpp>

#include "NodeRoot.h"
#include "Mouse.h"

namespace pkzo
{
    class Engine;
    class Screen;
    class Renderer;
    class HitArea;

    template <>
    struct NodeTraits<Screen>
    {
        using Matrix = glm::mat3;
    };

    class ICE_EXPORT Screen : public NodeRoot<Screen>
    {
    public:
        Screen();
        Screen(const glm::vec2& size);
        ~Screen() = default;

        const glm::vec2& get_size() const noexcept;
        void resize(const glm::vec2& value) noexcept;

        Renderer* get_renderer() noexcept;
        const Renderer* get_renderer() const noexcept;

        void draw();

        void activate() override;
        void deactivate() override;

        void handle_mouse_down(const MouseButton button, const glm::vec2& pos);
        void handle_mouse_up(const MouseButton button, const glm::vec2& pos);

    private:
        glm::vec2             size;
        unsigned int          camera_handle = 0;
        Renderer*             renderer      = nullptr;
        std::vector<HitArea*> hitareas;

        void add_hitarea(HitArea* ha);
        void remove_hitarea(HitArea* ha);

        friend class HitArea;
    };

    ICE_EXPORT glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos);
}