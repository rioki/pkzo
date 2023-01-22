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
#include "MenuItem.h"

#include "Style.h"
#include "PopupMenu.h"

namespace pkzo
{
    MenuItem::MenuItem(const std::shared_ptr<Style>& style, const std::string& caption, const std::function<void ()>& cb)
    : Button(style->get_vec2("MenuItem", "size"),
             caption,
             style->get_font("MenuItem", "font"),
             style->get_color("MenuItem", "color"),
             style->get_color("MenuItem", "background_color"),
             style->get_texture("MenuItem", "background_texture"))
    {
        on_click(cb);
    }

    MenuItem::MenuItem(const std::shared_ptr<Style>& style, const std::string& caption, const std::shared_ptr<PopupMenu>& menu)
    : MenuItem(style, caption, c9y::sync_fun(rsig::mem_fun(this, &MenuItem::show_submenu)))
    {
        submenu = menu;
        click_out_conn = submenu->on_click_out(c9y::sync_fun(rsig::mem_fun(this, &MenuItem::hide_submenu)));
    }

    MenuItem::~MenuItem()
    {
        if (submenu)
        {
            submenu->get_click_out_signal().disconnect(click_out_conn);
        }
    }

    void MenuItem::toggle_submenu()
    {
        assert(submenu);
        if (submenu->get_parent() == nullptr)
        {
            show_submenu();
        }
        else
        {
            hide_submenu();
        }
    }

    void MenuItem::show_submenu()
    {
        assert(submenu);
        if (submenu->get_parent() == nullptr && just_closed == false)
        {
            // TODO compute position
            auto hs = get_size() * 0.5f;
            auto wt = glm::vec2(get_world_transform()[2]);
            auto mp = wt - hs;
            auto sp = mp + (submenu->get_size() * glm::vec2(0.5f, -0.5f));
            submenu->set_position(sp);

            auto root = get_root();
            assert(root);
            root->add_node(submenu);
        }
    }

    void MenuItem::hide_submenu()
    {
        assert(submenu);
        if (submenu->get_parent() != nullptr)
        {
            auto root = get_root();
            assert(root);
            root->remove_node(submenu);
            just_closed = true;
            c9y::sync([this] () {
                just_closed = false;
            });
        }
    }
}
