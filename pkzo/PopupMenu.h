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

#include <memory>

#include "Menu.h"
#include "Style.h"

namespace pkzo
{
    //! Pupup Menu
    class ICE_EXPORT PopupMenu : public Menu
    {
    public:
        //! Create a pop up menu
        //!
        //! @param position the position the pop up menu shall appear
        //! @param style the style of the menu
        //! @{
        PopupMenu(const std::shared_ptr<Style>& style);
        PopupMenu(const glm::vec2& position, const std::shared_ptr<Style>& style);
        //! @}

        //! Singal emitted when the user click outside of the pop up menu.
        //!
        //! This signal can be used to hide the menu again, if the user clicked somewhere else.
        //!
        //! @{
        [[nodiscard]] rsig::signal<>& get_click_out_signal() noexcept;
        rsig::connection on_click_out(const std::function<void ()>& cb) noexcept;
        //! @}

        [[nodiscard]] glm::vec2 get_min_size() const noexcept override;

    protected:
        [[nodiscard]] glm::vec2 handle_size_request(const glm::vec2& value) noexcept override;

    private:
        rsig::signal<>             click_out_signal;
        std::shared_ptr<Rectangle> background;
        std::shared_ptr<HitArea>   hit_area;
    };
}
