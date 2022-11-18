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

#include "Widget.h"

namespace ice::ui
{
    using stdex::in;
    using stdex::cref_t;

    class ICE_EXPORT CheckBox : public Widget
    {
    public:
        CheckBox(in<std::shared_ptr<Style>> style, in<bool> checked, in<std::string> caption);
        CheckBox(in<glm::vec2> position, in<std::shared_ptr<Style>> style, in<bool> checked, in<std::string> caption);
        CheckBox(in<glm::vec2> position, in<bool> checked, in<std::shared_ptr<Texture>> checked_texture, in<std::shared_ptr<Texture>> unchecked_texture, in<glm::vec4> checkbox_color, in<std::string> caption, in<std::shared_ptr<Font>> font, in<glm::vec4> color) noexcept;

        void set_caption(in<std::string> value) noexcept;
        [[nodiscard]] in<std::string> get_caption() const noexcept;

        void set_checked(bool value) noexcept;
        [[nodiscard]] bool get_checked() const noexcept;

        void set_style(in<std::shared_ptr<Style>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Style>> get_style() const noexcept;

        void set_checked_texture(in<std::shared_ptr<Texture>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Texture>> get_checked_texture() const noexcept;

        void set_unchecked_texture(in<std::shared_ptr<Texture>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Texture>> get_unchecked_texture() const noexcept;

        void set_checkbox_color(in<glm::vec4> value) noexcept;
        [[nodiscard]] cref_t<glm::vec4> get_checkbox_color() const noexcept;

        void set_font(in<std::shared_ptr<Font>> value) noexcept;
        [[nodiscard]] cref_t<std::shared_ptr<Font>> get_font() const noexcept;

        void set_color(in<glm::vec4> value) noexcept;
        [[nodiscard]] cref_t<glm::vec4> get_color() const noexcept;

        rsig::connection on_click(const std::function<void ()>& cb) noexcept;
        [[nodiscard]] rsig::signal<>& get_click_signal() noexcept;

        [[nodiscard]] glm::vec2 get_min_size() const noexcept override;

    protected:
        [[nodiscard]] glm::vec2 handle_size_request(const glm::vec2& value) noexcept override;

    private:
        bool                     checked = false;
        std::shared_ptr<Style>   style;
        std::shared_ptr<Texture> checked_texture;
        std::shared_ptr<Texture> unchecked_texture;
        Rectangle                checkbox;
        Text                     label;
        HitArea                  hit_area;

        void layout();
    };
}
