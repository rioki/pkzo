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
#include "TableLayout.h"

namespace pkzo
{
    TableLayout::TableLayout() = default;

    TableLayout::TableLayout(unsigned int c, float m)
    : columns(c), horizontal_margin(m), vertical_margin(m) {}

    TableLayout::TableLayout(unsigned int c, float hm, float vm)
    : columns(c), horizontal_margin(hm), vertical_margin(vm) {}

    TableLayout::TableLayout(const glm::vec2& position)
    : Layout(position) {}

    TableLayout::TableLayout(const glm::vec2& position, unsigned int c, float m)
    : Layout(position), columns(c), horizontal_margin(m), vertical_margin(m) {}

    TableLayout::TableLayout(const glm::vec2& position, unsigned int c, float hm, float vm)
    : Layout(position), columns(c), horizontal_margin(hm), vertical_margin(vm) {}

    void TableLayout::set_columns(unsigned int value) noexcept
    {
        columns = value;
        place_elements();
    }

    unsigned int TableLayout::get_columns() const noexcept
    {
        return columns;
    }

    void TableLayout::set_horizontal_margin(float value) noexcept
    {
        horizontal_margin = value;
        place_elements();
    }

    float TableLayout::get_horizontal_margin() const noexcept
    {
        return horizontal_margin;
    }

    void TableLayout::set_vertical_margin(float value) noexcept
    {
        vertical_margin = value;
        place_elements();
    }

    float TableLayout::get_vertical_margin() const noexcept
    {
        return vertical_margin;
    }

    void TableLayout::set_margin(float value) noexcept
    {
        horizontal_margin = value;
        vertical_margin = value;
        place_elements();
    }

    glm::vec2 TableLayout::get_min_size() const noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return glm::vec2(0.0f);
        }

        auto column_widths = std::vector<float>(columns, 0.0f);
        auto row_heights   = std::vector<float>(1);

        auto column = 0;
        auto row    = 0;
        for (const auto* widget : widgets)
        {
            auto ms = widget->get_min_size();

            column_widths[column] = std::max(ms.x, column_widths[column]);
            row_heights[row]      = std::max(ms.y, row_heights[row]);

            column++;
            if (column % columns == 0)
            {
                column = 0;
                row++;
                row_heights.push_back(0.0f);
            }
        }

        return calc_size({column_widths, row_heights});
    }

    glm::vec2 TableLayout::handle_size_request(const glm::vec2& value) noexcept
    {
        auto nsize = glm::max(get_min_size(), value);
        place_elements();
        return nsize;
    }

    void TableLayout::handle_list_change() noexcept
    {
        set_size(calc_size(calc_sizes()));
        place_elements();
    }

    glm::vec2 TableLayout::calc_size(const std::tuple<std::vector<float>, std::vector<float>>& values) const noexcept
    {
        return glm::vec2(
            std::accumulate(begin(std::get<0>(values)), end(std::get<0>(values)), 0.0f) + (static_cast<float>(std::get<0>(values).size() - 1)) * horizontal_margin,
            std::accumulate(begin(std::get<1>(values)), end(std::get<1>(values)), 0.0f) + (static_cast<float>(std::get<1>(values).size() - 1)) * vertical_margin
        );
    }

    std::tuple<std::vector<float>, std::vector<float>> TableLayout::calc_sizes() const noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return {};
        }

        auto column_widths = std::vector<float>(columns, 0.0f);
        auto row_heights   = std::vector<float>(1);

        auto column = 0;
        auto row    = 0;
        for (const auto* widget : widgets)
        {
            auto ms = widget->get_min_size();

            column_widths[column] = std::max(ms.x, column_widths[column]);
            row_heights[row]      = std::max(ms.y, row_heights[row]);

            column++;
            if (column % columns == 0)
            {
                column = 0;
                row++;
                row_heights.push_back(0.0f);
            }
        }

        return {column_widths, row_heights};
    }

    void TableLayout::place_elements() noexcept
    {
        auto widgets = get_nodes<Widget>();
        if (widgets.empty())
        {
            return;
        }

        const auto hs = get_size() * 0.5f;
        auto position = glm::vec2(-hs.x, hs.y);

        auto [column_widths, row_heights] = calc_sizes();

        auto column = 0;
        auto row    = 0;
        position.y -= row_heights[row] * 0.5f;
        for (auto* widget : widgets)
        {
            position.x += column_widths[column] * 0.5f;
            widget->set_position(position);
            position.x += column_widths[column] * 0.5f + horizontal_margin;

            column++;
            if (column % columns == 0)
            {
                position.y -=  row_heights[row] * 0.5f + vertical_margin;
                column = 0;
                row++;
                position.x = -hs.x;
                position.y -= row_heights[row] * 0.5f;
            }
        }
    }
}
