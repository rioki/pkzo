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

#include <c9y/c9y.h>
#include <rsig/rsig.h>

#include "Button.h"
#include "Text.h"

namespace pkzo
{
    class PopupMenu;

    class ICE_EXPORT MenuItem : public Button
    {
    public:
        MenuItem(const std::shared_ptr<Style>& style, const std::string& caption, const std::function<void ()>& cb);
        MenuItem(const std::shared_ptr<Style>& style, const std::string& caption, const std::shared_ptr<PopupMenu>& menu);

        ~MenuItem();

    private:
        std::shared_ptr<PopupMenu> submenu;
        rsig::connection           click_out_conn;

        bool just_closed = false;

        void toggle_submenu();
        void show_submenu();
        void hide_submenu();
    };
}
