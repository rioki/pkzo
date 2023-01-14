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

#include "Layout.h"

namespace pkzo
{
    //! Table Layout
    class ICE_EXPORT TableLayout : public Layout
    {
    public:
        //! Construct Vertical Layout
        //!
        //! @param position initial position
        //! @param columns the number of columns
        //! @param margin the margin to use
        //! @param horizontal_margin the horizontal margin to use
        //! @param vertical_margin the verical margin to use
        //! @{
        TableLayout();
        TableLayout(unsigned int columns, float margin);
        TableLayout(unsigned int columns, float horizontal_margin, float vertical_margin);
        TableLayout(const glm::vec2& position);
        TableLayout(const glm::vec2& position, unsigned int columns, float margin);
        TableLayout(const glm::vec2& position, unsigned int columns, float horizontal_margin, float vertical_margin);
        //! @}

        //! Number of Columns
        //! @{
        void set_columns(unsigned int value) noexcept;
        unsigned int get_columns() const noexcept;
        //! @}

        //! Horizontal Margin
        //! @{
        void set_horizontal_margin(float value) noexcept;
        float get_horizontal_margin() const noexcept;
        //! @}

        //! Vertical Margin
        //! @{
        void set_vertical_margin(float value) noexcept;
        float get_vertical_margin() const noexcept;
        //! @}

        //! Set both vertical and horizontal margins.
        void set_margin(float value) noexcept;

        glm::vec2 get_min_size() const noexcept override;

    protected:
        glm::vec2 handle_size_request(const glm::vec2& value) noexcept override;
        void handle_list_change() noexcept override;

    private:
        unsigned int  columns = 2;
        float         horizontal_margin  = 5.0f;
        float         vertical_margin    = 5.0f;

        glm::vec2 calc_size(const std::tuple<std::vector<float>, std::vector<float>>& values) const noexcept;
        std::tuple<std::vector<float>, std::vector<float>> calc_sizes() const noexcept;
        void place_elements() noexcept;
    };
}
