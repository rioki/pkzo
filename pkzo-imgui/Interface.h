// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include <string>
#include <functional>
#include <vector>

#include <pkzo/pkzo.h>

#include "defines.h"

struct ImGuiContext;

namespace pkzo::imgui
{
    //! User Interface using ImGui
    class PKZO_IMGUI_EXPORT Interface
    {
    public:
        Interface();
        Interface(const Interface&) = delete;

        ~Interface();
        Interface& operator = (const Interface&) = delete;

        //! Add a menu item with an action.
        //!
        //! This function will add a menu item to the main menu and if that item is selected call the given callback.
        //!
        //! @param menu the name of the menu, eg: File
        //! @param item the name of the item, eg: Open
        //! @param shortcut the shortcut to display, eg: CTRL+O
        //! @param cb the callback to call when the menu item is called.
        void add_menu_action(const std::string& menu, const std::string& item, const std::string& shortcut, const std::function<void()>& cb);

        //! Add a menu item with a window.
        //!
        //! This function will add a menu tiem to the main menu and if that item is sellected call the given callback, that
        //! then can render a window using ImGui functions. The boolean in the ballback function shoult be passed on
        //! ImGui::Begin as the paremeter to show and hide the window.
        //!
        //! @param menu the name of the menu, eg: File
        //! @param item the name of the item, eg: Open
        //! @param shortcut the shortcut to display, eg: CTRL+O
        //! @param cb the callback to call to draw the window
        void add_window(const std::string& menu, const std::string& item, const std::string& shortcut, const std::function<void(bool&)>& cb);

        //! Get the ImGui context.
        //!
        //! When calling ImGui function you need to set the current context.
        //! Use this function to get the appropriate context and set
        //! it with ImGui::SetCurrentContext.
        ImGuiContext* get_context() const noexcept;

        //! Froward input to ImGui
        //!
        //! @{
        void handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos);
        void handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos);
        void handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel);
        void handle_mouse_wheel(glm::ivec2 rel);

        void handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key);
        void handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key);
        void handle_keboard_text(const std::string_view text);
        //! @}

        //! Actually draw the user interface.
        void draw(glm::uvec2 size, glm::uvec2 draw_size);

    private:
        struct MenuItem
        {
            std::string name;
            std::string accell;
            std::function<void ()> action;
        };

        struct Menu
        {
            std::string name;
            std::vector<MenuItem> items;
        };

        struct Window
        {
            std::function<void (bool&)> draw_func;
            bool visible = false;
        };

        std::vector<Menu> main_menu;
        std::vector<Window> windows;

        void draw_main_menu();
        void draw_windows();

    };
}