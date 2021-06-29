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

namespace pkzo
{
    DropDownMenu::DropDownMenu(const glm::mat4& transform, 
                               const glm::vec2& s, const std::shared_ptr<pkzo::Material>& background_material, 
                               const glm::vec2& button_size, const std::shared_ptr<pkzo::Material>& button_material, 
                               const glm::vec2& mhs, const glm::vec2& mis, const glm::vec2& mfs,
                               const std::shared_ptr<pkzo::Material>& mtop, const std::shared_ptr<pkzo::Material>& mbdy, const std::shared_ptr<pkzo::Material>& mbtm,
                               const std::shared_ptr<pkzo::Font>& f, const std::shared_ptr<pkzo::Material>& tm,
                               const std::vector<std::string>& o, std::optional<size_t> so) noexcept
    : SceneNodeGroup(transform), 
      size(s), options(o), selected_option(so),
      menu_header_size(mhs), menu_item_size(mis), menu_footer_size(mfs), menu_top(mtop), menu_body(mbdy), menu_bottom(mbtm),
      font(f), text_material(tm)
    {
        auto background = std::make_shared<Rectangle>(size, background_material);
        add_node(background);

        auto label = selected_option ? options[selected_option.value()] : std::string();
        selected_text = std::make_shared<Text>(label, font, text_material);
        add_node(selected_text);

        auto button = std::make_shared<Button>(position({ size.x / 2.0f - button_size.x / 2.0f, 0.0f }), button_size, button_material);
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

        auto parent = dynamic_cast<SceneNodeGroup*>(get_parent());
        if (parent)
        {
            menu = std::make_shared<Menu>(menu_header_size, menu_top, menu_item_size, menu_body, menu_footer_size, menu_bottom, font, text_material, options);
            auto size = get_size();
            auto menu_transform = get_transform();
            menu_transform = glm::translate(menu_transform, {0.0f, -size.y / 2.0f - menu->get_size().y / 2.0f , 0.0f});
            menu->set_transform(menu_transform);
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

        auto parent = dynamic_cast<SceneNodeGroup*>(get_parent());
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
