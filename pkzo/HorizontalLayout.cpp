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

#include "pch.h"
#include "HorizontalLayout.h"

namespace pkzo
{
    HorizontalLayout::HorizontalLayout() = default;

    HorizontalLayout::HorizontalLayout(float _margin)
    : margin(_margin) {}

    HorizontalLayout::HorizontalLayout(const glm::vec2& _position)
    : Layout(_position) {}

    HorizontalLayout::HorizontalLayout(const glm::vec2& _position, float _margin)
    : Layout(_position), margin(_margin) {}

    void HorizontalLayout::set_margin(const float value) noexcept
    {
        margin = value;
        place_elements();
    }

    float HorizontalLayout::get_margin() const noexcept
    {
        return margin;
    }

    glm::vec2 HorizontalLayout::get_min_size() const noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return glm::vec2(0.0f);
        }

        auto result = glm::vec2(0.0f, 0.0f);

        for (const auto* widget : widgets)
        {
            auto ms = widget->get_min_size();
            result.x += ms.x;
            result.x += margin;
            result.y = std::max(ms.y, result.y);
        }

        // remove last margin, as it was added to much
        result.x -= margin;

        return result;
    }

    glm::vec2 HorizontalLayout::handle_size_request(const glm::vec2& value) noexcept
    {
        auto nsize = glm::max(get_min_size(), value);
        place_elements();
        return nsize;
    }

    void HorizontalLayout::handle_list_change() noexcept
    {
        set_size(calc_size());
        place_elements();
    }

    glm::vec2 HorizontalLayout::calc_size() const noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return glm::vec2(0.0f);
        }

        auto result = glm::vec2(0.0f, 0.0f);

        for (const auto* widget : widgets)
        {
            auto ms = widget->get_size();
            result.x += ms.x;
            result.x += margin;
            result.y = std::max(ms.y, result.y);
        }

        // remove last margin, as it was added to much
        result.x -= margin;

        return result;
    }

    void HorizontalLayout::place_elements() noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return;
        }

        const auto hs = get_size() * 0.5f;
        auto position = glm::vec2(-hs.x, 0.0f);

        for (auto* widget : widgets)
        {
            auto es = widget->get_size();
            position.x += es.x * 0.5f;
            widget->set_position(position);
            position.x += es.x * 0.5f + margin;
        }
    }
}
