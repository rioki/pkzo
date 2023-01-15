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

#include "ScreenNodeGroup.h"

#include "Style.h"

namespace pkzo
{
    class ICE_EXPORT Widget : public ScreenNodeGroup
    {
    public:

        Widget() noexcept;
        Widget(const glm::vec2& size) noexcept;
        Widget(const glm::vec2& position, const glm::vec2& size) noexcept;

        void set_position(const glm::vec2& value) noexcept;
        glm::vec2 get_position() const noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        virtual glm::vec2 get_min_size() const noexcept;

    protected:
        virtual glm::vec2 handle_size_request(const glm::vec2& value) noexcept;

    private:
        glm::vec2 size = glm::vec2(0.0f);
    };
}