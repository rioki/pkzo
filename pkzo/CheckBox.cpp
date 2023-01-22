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

#include "pch.h"
#include "CheckBox.h"

#include "Style.h"

namespace pkzo
{
    constexpr auto CHECKBOX_PADDING = 5.0f;

    glm::vec2 get_checkbox_size(in<std::shared_ptr<Texture>> checked_texture, in<std::shared_ptr<Texture>> unchecked_texture)
    {
        assert(checked_texture);
        assert(unchecked_texture);
        return glm::vec2(glm::min(checked_texture->get_size(), unchecked_texture->get_size()));
    }

    cref_t<std::shared_ptr<Texture>> get_checkbox_texture(in<bool> checked, in<std::shared_ptr<Texture>> checked_texture, in<std::shared_ptr<Texture>> unchecked_texture)
    {
        return checked ? checked_texture : unchecked_texture;
    }

    glm::vec2 estimate_size(in<std::shared_ptr<Texture>> checked_texture, in<std::shared_ptr<Texture>> unchecked_texture, in<glm::vec2> label_size)
    {
        auto checked_size = get_checkbox_size(checked_texture, unchecked_texture);
        return {
            CHECKBOX_PADDING + checked_size.x + CHECKBOX_PADDING + label_size.x + CHECKBOX_PADDING,
            std::max(checked_size.y + 2.0f * CHECKBOX_PADDING, label_size.x + 2.0f * CHECKBOX_PADDING)
        };
    }

    glm::vec2 estimate_size(in<std::shared_ptr<Texture>> checked_texture, in<std::shared_ptr<Texture>> unchecked_texture, in<std::string> caption, in<std::shared_ptr<Font>> font)
    {
        return estimate_size(checked_texture, unchecked_texture, font->estimate(caption));
    }

    CheckBox::CheckBox(in<std::shared_ptr<Style>> style, in<bool> checked, in<std::string> caption)
    : CheckBox(glm::vec2(0.0f), style, checked, caption) {}

    CheckBox::CheckBox(in<glm::vec2> _position, in<std::shared_ptr<Style>> _style, in<bool> _checked, in<std::string> _caption)
    : CheckBox(_position,
               _checked,
               _style->get_texture("CheckBox", "checked_texture"),
               _style->get_texture("CheckBox", "unchecked_texture"),
               _style->get_color("CheckBox", "checkbox_color"),
               _caption,
               _style->get_font("CheckBox", "font"),
               _style->get_color("CheckBox", "color"))
    {
        style = _style;
    }

    CheckBox::CheckBox(in<glm::vec2> _position, in<bool> _checked, in<std::shared_ptr<Texture>> _checked_texture, in<std::shared_ptr<Texture>> _unchecked_texture, in<glm::vec4> _checkbox_color, in<std::string> _caption, in<std::shared_ptr<Font>> _font, in<glm::vec4> _color) noexcept
    : Widget(_position, estimate_size(_checked_texture, _unchecked_texture, _caption, _font)),
      checked_texture(_checked_texture),
      unchecked_texture(_unchecked_texture),
      checkbox(glm::mat4(1.0f), get_checkbox_size(_checked_texture, _unchecked_texture), _checkbox_color, get_checkbox_texture(_checked, _checked_texture, _unchecked_texture)),
      label(glm::mat4(1.0f), _caption, _font, _color),
      hit_area(glm::mat4(1.0f), get_size())
    {
        add_node(checkbox);
        add_node(label);
        add_node(hit_area);

        hit_area.on_click([this]() {
            checked = !checked;
            checkbox.set_texture(get_checkbox_texture(checked, checked_texture, unchecked_texture));
        });

        layout();
    }

    void CheckBox::set_caption(in<std::string> value) noexcept
    {
        label.set_text(value);
    }

    [[nodiscard]] in<std::string> CheckBox::get_caption() const noexcept
    {
        return label.get_text();
    }

    void CheckBox::set_checked(bool value) noexcept
    {
        checked = value;
        checkbox.set_texture(get_checkbox_texture(checked, checked_texture, unchecked_texture));
    }

    [[nodiscard]] bool CheckBox::get_checked() const noexcept
    {
        return checked;
    }

    void CheckBox::set_style(in<std::shared_ptr<Style>> value) noexcept
    {
        style = value;

        checked_texture  = style->get_texture("CheckBox", "checked_texture");
        unchecked_texture = style->get_texture("CheckBox", "unchecked_texture");

        checkbox.set_size(get_checkbox_size(checked_texture, unchecked_texture));
        checkbox.set_texture(get_checkbox_texture(checked, checked_texture, unchecked_texture));

        label.set_font(style->get_font("CheckBox", "font"));
        label.set_color(style->get_color("CheckBox", "color"));

        set_size(estimate_size(checked_texture, unchecked_texture, label.get_size()));
        layout();
    }

    [[nodiscard]] cref_t<std::shared_ptr<Style>> CheckBox::get_style() const noexcept
    {
        return style;
    }

    void CheckBox::set_checked_texture(in<std::shared_ptr<Texture>> value) noexcept
    {
        checked_texture = value;

        checkbox.set_size(get_checkbox_size(checked_texture, unchecked_texture));
        checkbox.set_texture(get_checkbox_texture(checked, checked_texture, unchecked_texture));

        set_size(estimate_size(checked_texture, unchecked_texture, label.get_size()));
        layout();
    }

    [[nodiscard]] cref_t<std::shared_ptr<Texture>> CheckBox::get_checked_texture() const noexcept
    {
        return checked_texture;
    }

    void CheckBox::set_unchecked_texture(in<std::shared_ptr<Texture>> value) noexcept
    {
        unchecked_texture = value;

        checkbox.set_size(get_checkbox_size(checked_texture, unchecked_texture));
        checkbox.set_texture(get_checkbox_texture(checked, checked_texture, unchecked_texture));

        set_size(estimate_size(checked_texture, unchecked_texture, label.get_size()));
        layout();
    }

    [[nodiscard]] cref_t<std::shared_ptr<Texture>> CheckBox::get_unchecked_texture() const noexcept
    {
        return unchecked_texture;
    }

    void CheckBox::set_checkbox_color(in<glm::vec4> value) noexcept
    {
        checkbox.set_color(value);
    }

    [[nodiscard]] cref_t<glm::vec4> CheckBox::get_checkbox_color() const noexcept
    {
        return checkbox.get_color();
    }

    void CheckBox::set_font(in<std::shared_ptr<Font>> value) noexcept
    {
        label.set_font(value);

        set_size(estimate_size(checked_texture, unchecked_texture, label.get_size()));
        layout();
    }

    [[nodiscard]] cref_t<std::shared_ptr<Font>> CheckBox::get_font() const noexcept
    {
        return label.get_font();
    }

    void CheckBox::set_color(in<glm::vec4> value) noexcept
    {
        label.set_color(value);
    }

    [[nodiscard]] cref_t<glm::vec4> CheckBox::get_color() const noexcept
    {
        return label.get_color();
    }

    rsig::connection CheckBox::on_click(const std::function<void ()>& cb) noexcept
    {
        return hit_area.on_click(cb);
    }

    [[nodiscard]] rsig::signal<>& CheckBox::get_click_signal() noexcept
    {
        return hit_area.get_click_signal();
    }

    [[nodiscard]] glm::vec2 CheckBox::get_min_size() const noexcept
    {
        return estimate_size(checked_texture, unchecked_texture, label.get_size());
    }

    [[nodiscard]] glm::vec2 CheckBox::handle_size_request(const glm::vec2& value) noexcept
    {
        auto ms = glm::max(get_min_size(), value);
        hit_area.set_size(ms);
        return ms;
    }

    void CheckBox::layout()
    {
        auto hs = get_size() / 2.0f;
        checkbox.set_transform(glm::translate(glm::vec2(-hs.x + CHECKBOX_PADDING + checkbox.get_size().x / 2.0f, 0.0f)));
        label.set_transform(glm::translate(glm::vec2(hs.x - CHECKBOX_PADDING - label.get_size().x / 2.0f, 0.0f)));
        hit_area.set_size(get_size());
    }
}
