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

#pragma once

#include "config.h"

#include <vector>
#include <optional>
#include <string>
#include <memory>

#include "SceneNodeGroup.h"

namespace pkzo
{
    class Menu;
    class Texture;
    class Text;
    class Font;

    class PKZO_EXPORT DropDownMenu : public SceneNodeGroup
    {
    public:
        DropDownMenu(const std::shared_ptr<pkzo::Texture>& background_texture, const std::shared_ptr<pkzo::Texture>& button_texture, const std::shared_ptr<pkzo::Texture>& menu_top_texture, const std::shared_ptr<pkzo::Texture>& menu_body_texture, const std::shared_ptr<pkzo::Texture>& menu_bottom_texture, const std::shared_ptr<Font>& font, const glm::vec4& text_color) noexcept;
        ~DropDownMenu();

        glm::vec2 get_size() const noexcept;

        void set_options(const std::vector<std::string>& value) noexcept;
        const std::vector<std::string>& get_options() const noexcept;

        void set_selected_option(std::optional<size_t> value) noexcept;
        std::optional<size_t> get_selected_option() const noexcept;

        void on_select(const std::function<void (size_t)>& cb);

    private:
        glm::vec2                size;
        std::vector<std::string> options;
        std::optional<size_t>    selected_option;

        std::shared_ptr<Text>    selected_text;
        std::shared_ptr<Texture> menu_top_texture;
        std::shared_ptr<Texture> menu_body_texture;
        std::shared_ptr<Texture> menu_bottom_texture;
        std::shared_ptr<Font>    font;
        glm::vec4                text_color;
        std::shared_ptr<Menu>    menu;

        std::function<void (size_t)> select_cb;

        void show_menu();
        void close_menu(std::optional<size_t> value);
    };
}
