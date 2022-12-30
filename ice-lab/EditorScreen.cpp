// Ice Engine
// Copyright 2022 Sean Farrell
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
#include "EditorScreen.h"

#include "LabEngine.h"

namespace lab
{
    EditorScreen::EditorScreen(LabEngine& engine, const glm::uvec2 size)
    : Screen(size)
    {
        auto style = engine.load_asset<ice::ui::Style>("ui/DarkBlue.json");
        assert(style);

        auto main_menu = std::make_shared<ice::ui::MenuBar>(style);

        auto file_menu = std::make_shared<ice::ui::PopupMenu>(style);

        file_menu->add_item("New Scene", [this] () {});
        file_menu->add_item("Open Scene", [this] () {});
        file_menu->add_item("Save Scene", [this] () {});
        file_menu->add_item("Save Scene As", [this] () {});
        file_menu->add_item("New Scene", [this] () {});
        file_menu->add_item("Exit", [&engine] () {
            engine.stop();
        });

        main_menu->add_item("File", file_menu);

        auto edit_menu = std::make_shared<ice::ui::PopupMenu>(style);

        edit_menu->add_item("Undo", [this] () {});
        edit_menu->add_item("Redo", [this] () {});
        edit_menu->add_item("Settings", [this] () {});

        main_menu->add_item("Edit", edit_menu);

        auto help_menu = std::make_shared<ice::ui::PopupMenu>(style);

        help_menu->add_item("About Ice Engine", [this] () {});

        main_menu->add_item("Help", help_menu);

        add_node(main_menu);

        main_menu->set_size(glm::vec2(size.x, main_menu->get_size().y));
        main_menu->set_position(glm::vec2(0.0f, (size.y / 2.0f) - (main_menu->get_size().y / 2.0f)));
    }
}
