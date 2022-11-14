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

#include <ice/Text.h>

#include "Widget.h"

namespace ice::ui
{
    using stdex::in;
    using stdex::cref_t;

    enum class TextStyle
    {
        DEFAULT,
        TITLE,
        SUBTITLE,
        HEADING1,
        HEADING2,
        HEADING3,
        HEADING4,
        HEADING5,
        BOLD,
        ITALLIC,
        BOLD_ITALIC,
        CODE
    };

    class ICE_EXPORT Label : public Widget
    {
    public:
        Label() noexcept;
        Label(in<std::shared_ptr<Style>> style, in<std::string> caption);
        Label(in<std::shared_ptr<Style>> style, in<TextStyle> variant, in<std::string> caption);
        Label(in<glm::vec2> position, in<std::shared_ptr<Style>> style, in<std::string> caption);
        Label(in<glm::vec2> position, in<std::shared_ptr<Style>> style, in<TextStyle> variant, in<std::string> caption);
        Label(in<std::string> text, in<std::shared_ptr<Font>> font, in<glm::vec4> color) noexcept;
        Label(in<glm::vec2> position, in<std::string> text, in<std::shared_ptr<Font>> font, in<glm::vec4> color) noexcept;

        void set_caption(in<std::string> value) noexcept;
        [[nodiscard]] in<std::string> get_caption() const noexcept;

        void set_variant(in<TextStyle> value) noexcept;
        [[nodiscard]] cref_t<TextStyle> get_variant() const noexcept;

        void set_style(in<std::shared_ptr<Style>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Style>> get_style() const noexcept;

        void set_font(in<std::shared_ptr<Font>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Font>> get_font() const noexcept;

        void set_color(in<glm::vec4> value) noexcept;
        [[nodiscard]] cref_t<glm::vec4> get_color() const noexcept;

        [[nodiscard]] glm::vec2 get_min_size() const noexcept override;

    protected:
        [[nodiscard]] glm::vec2 handle_size_request(const glm::vec2& value) noexcept override;

    private:
        std::shared_ptr<Style> style;
        TextStyle            variant;
        Text                   label;
    };
}
