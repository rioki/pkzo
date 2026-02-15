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

#include "Group.h"

namespace pkzo2d
{
    class Renderer;

    class PKZO2D_EXPORT Screen : public Group
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

        Renderer* get_renderer();

        void draw(pkzo::GraphicContext& gc);

    private:
        glm::vec2                 size;
        std::unique_ptr<Renderer> renderer;
    };

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
