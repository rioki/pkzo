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

#include <pkzo/GraphicContext.h>

#include "events.h"
#include "Group.h"

namespace pkzo
{
    class ScreenRenderer;

    class Screen;

    template <>
    struct NodeTraits<Screen>
    {
        using Matrix = glm::mat3;
    };

    using ScreenNode  = Node<Screen>;
    using ScreenGroup = Group<Screen>;

    class PKZO_EXPORT Screen : public ScreenGroup
    {
    public:
        struct Specs
        {
            glm::vec2 size = glm::vec2(600.0f, 800.0f);
        };

        Screen(Specs specs);

        ~Screen();

        void set_size(const glm::vec2& value);
        const glm::vec2& get_size() const;

        ScreenRenderer* get_renderer();

        void draw(pkzo::GraphicContext& gc);

        //! Register an input handler on the screen.
        //!
        //! @note This singal is primarily intended for nodes to observe input.
        rsig::connection on_input(const std::function<void (const InputEvent&)>& handler);

        //! Forward an input event to a Screen for processing.
        void handle_input(const InputEvent& event);

    private:
        glm::vec2                 size;
        std::unique_ptr<ScreenRenderer> renderer;
        rsig::signal<const InputEvent&> input_signal;
    };

    constexpr glm::mat3 position(const glm::vec2& value)
    {
        return glm::translate(glm::mat3(1.0f), value);
    }

    constexpr glm::mat3 position(float x, float y)
    {
        return position(glm::vec2(x, y));
    }

    template <typename T>
    inline T map(T source_left, T source_right, T target_left, T target_right, T value)
    {
        auto source_range = source_right - source_left;
        auto target_range = target_right - target_left;
        return (value - source_left) * (target_range / source_range) + target_left;
    }

    inline glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos)
    {
        auto hs = screen_size / 2.0f;
        return {
            map<float>(0.0f, win_size.x, -hs.x,  hs.x, pos.x),
            map<float>(0.0f, win_size.y,  hs.y, -hs.y, pos.y)
        };
    }
}
