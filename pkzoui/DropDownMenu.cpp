//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "DropDownMenu.h"

#include <pkzo/sync.h>

#include "Button.h"
#include "Menu.h"

namespace pkzoui
{
    DropDownMenu::DropDownMenu(const std::shared_ptr<pkzo::Texture>& background_texture, const std::shared_ptr<pkzo::Texture>& button_texture, const std::shared_ptr<pkzo::Texture>& mtt, const std::shared_ptr<pkzo::Texture>& mbt, const std::shared_ptr<pkzo::Texture>& mbot, const std::shared_ptr<Font>& f, const glm::vec4& tc) noexcept
    : size(background_texture->get_size()), menu_top_texture(mtt), menu_body_texture(mbt), menu_bottom_texture(mbot), font(f), text_color(tc)
    {
        auto background = std::make_shared<Rectangle>(background_texture);
        add_node(background);

        selected_text = std::make_shared<Text>(font, text_color, "");
        add_node(selected_text);

        auto button = std::make_shared<Button>(button_texture);
        auto total_size = background->get_size();
        auto button_size = button->get_size();
        button->set_position({total_size.x / 2.0f - button_size.x / 2.0f, 0.0f});

        button->on_click([this] () {
            sync::delay([this] () {
                if (menu)
                {
                    close_menu(std::nullopt);
                }
                else
                {
                    show_menu();
                }
            });
        });
        add_node(button);
    }

    DropDownMenu::~DropDownMenu() = default;

    glm::vec2 DropDownMenu::get_size() const noexcept
    {
        return size;
    }

    void DropDownMenu::set_options(const std::vector<std::string>& value) noexcept
    {
        options = value;
    }

    const std::vector<std::string>& DropDownMenu::get_options() const noexcept
    {
        return options;
    }

    void DropDownMenu::set_selected_option(std::optional<size_t> value) noexcept
    {
        selected_option = value;
        if (selected_option && selected_option.value() < options.size())
        {
            selected_text->set_text(options[selected_option.value()]);
        }
        else
        {
            selected_text->set_text("");
        }
    }

    std::optional<size_t> DropDownMenu::get_selected_option() const noexcept
    {
        return selected_option;
    }

    void DropDownMenu::on_select(const std::function<void(size_t)>& cb)
    {
        select_cb = cb;
    }

    void DropDownMenu::show_menu()
    {
        assert(menu == nullptr);

        auto parent = dynamic_cast<ScreenNodeGroup*>(get_parent());
        if (parent)
        {
            menu = std::make_shared<Menu>(menu_top_texture, menu_body_texture, menu_bottom_texture, font, text_color, options);
            auto pos = get_position();
            auto size = get_size();
            menu->set_position({pos.x, pos.y - size.y / 2.0f - menu->get_size().y / 2.0f});
            menu->on_select([this] (auto selection) {
                sync::delay([this, selection] () {
                    close_menu(selection);
                });
            });
            parent->add_node(menu);
        }
    }

    void DropDownMenu::close_menu(std::optional<size_t> value)
    {
        assert(menu);

        auto parent = dynamic_cast<ScreenNodeGroup*>(get_parent());
        if (parent)
        {
            selected_option = value;
            if (value && select_cb)
            {
                select_cb(value.value());
            }
            if (selected_option)
            {
                assert(value < options.size());
                selected_text->set_text(options[selected_option.value()]);
            }

            parent->remove_node(menu);
            menu = nullptr;
        }
    }
}
