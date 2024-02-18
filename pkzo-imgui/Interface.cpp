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
// THE SOFTWARE..

#include "pch.h"
#include "Interface.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_pkzo.h"

namespace pkzo::imgui
{
    Interface::Interface()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplPkzo_Init();
        ImGui_ImplOpenGL3_Init("#version 430");
    }

    Interface::~Interface()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplPkzo_Shutdown();
        ImGui::DestroyContext();
    }

    void Interface::add_menu_action(const std::string& menu, const std::string & item, const std::string& shortcut, const std::function<void()>& cb)
    {
        auto i = std::find_if(begin(main_menu), end(main_menu), [&] (const auto& m) { return m.name == menu;});
        if (i == end(main_menu))
        {
            main_menu.push_back({menu, {}});
            i = main_menu.end() - 1;
        }
        i->items.push_back({item, shortcut, cb});
    }

    void Interface::add_window(const std::string& menu, const std::string& item, const std::string& shortcut, const std::function<void(bool&)>& cb)
    {
        auto idx = windows.size();
        windows.push_back({cb});
        add_menu_action(menu, item, shortcut, [=] () {
            windows.at(idx).visible = true;
        });
    }

    ImGuiContext* Interface::get_context() const noexcept
    {
        return ImGui::GetCurrentContext();
    }

    void Interface::handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos)
    {
        ImGui_ImplPkzo_HandleMouseButtonDown(button, pos);
    }

    void Interface::handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos)
    {
        ImGui_ImplPkzo_HandleMouseButtonUp(button, pos);
    }

    void Interface::handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel)
    {
        ImGui_ImplPkzo_HandleMouseMove(pos, rel);
    }

    void Interface::handle_mouse_wheel(glm::ivec2 rel)
    {
        ImGui_ImplPkzo_HandleMouseWheel(rel);
    }

    void Interface::handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key)
    {
        ImGui_ImplPkzo_HandleKeyDown(mod, key);
    }

    void Interface::handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key)
    {
        ImGui_ImplPkzo_HandleKeyUp(mod, key);
    }

    void Interface::handle_keboard_text(const std::string_view text)
    {
        ImGui_ImplPkzo_HandleText(text);
    }

    void Interface::draw(glm::uvec2 size, glm::uvec2 draw_size)
    {
        auto sec = glow::Section{"ImGui"};

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplPkzo_NewFrame(size, draw_size);
        ImGui::NewFrame();

        draw_main_menu();
        draw_windows();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Interface::draw_main_menu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (const auto& menu : main_menu)
            {
                if (ImGui::BeginMenu(menu.name.data()))
                {
                    for (auto& item : menu.items)
                    {
                        if (ImGui::MenuItem(item.name.data(), item.accell.data()))
                        {
                            if (item.action)
                            {
                                item.action();
                            }
                        }
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Interface::draw_windows()
    {
        for (auto& window : windows)
        {
            if (window.visible && window.draw_func)
            {
                window.draw_func(window.visible);
            }
        }
    }
}