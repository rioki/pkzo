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
#include <functional>

#include "Widget.h"
#include "Style.h"
#include "MenuItem.h"
#include "Layout.h"

namespace pkzo
{
    class PopupMenu;

    //! Menu Base
    class ICE_EXPORT Menu : public Widget
    {
    public:
        Menu(const std::shared_ptr<Style>& style);
        Menu(const glm::vec2& position, const std::shared_ptr<Style>& style);

        //! Add function item.
        //!
        //! @param caption the caption of the item
        //! @param function the function to call when the menu item is clicked.
        void add_item(const std::string& caption, const std::function<void ()>& function);

        //! Add item with submenu
        //!
        //! @param caption the caption of the item
        //! @param menu the menu to open when the menu item is clicked.
        void add_item(const std::string& caption, const std::shared_ptr<PopupMenu> menu);

    protected:
        const std::shared_ptr<Style> style;
        std::shared_ptr<Layout>      layout;
    };
}
