// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "imgui_impl_pkzo.h"

#include <SDL2/SDL.h>

char* g_clipboard_data = nullptr;
static const char* ImGui_ImplPkzo_GetClipboardText(void*)
{
    if (g_clipboard_data)
    {
        SDL_free(g_clipboard_data);
    }
    g_clipboard_data = SDL_GetClipboardText();
    return g_clipboard_data;
}

static void ImGui_ImplPkzo_SetClipboardText(void*, const char* text)
{
    SDL_SetClipboardText(text);
}

bool ImGui_ImplPkzo_Init()
{
    auto& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendPlatformName = "imgui_impl_pkzo";

    io.KeyMap[ImGuiKey_Tab]         = static_cast<int>(pkzo::Key::TAB);
    io.KeyMap[ImGuiKey_LeftArrow]   = static_cast<int>(pkzo::Key::LEFT);
    io.KeyMap[ImGuiKey_RightArrow]  = static_cast<int>(pkzo::Key::RIGHT);
    io.KeyMap[ImGuiKey_UpArrow]     = static_cast<int>(pkzo::Key::UP);
    io.KeyMap[ImGuiKey_DownArrow]   = static_cast<int>(pkzo::Key::DOWN);
    io.KeyMap[ImGuiKey_PageUp]      = static_cast<int>(pkzo::Key::PAGEUP);
    io.KeyMap[ImGuiKey_PageDown]    = static_cast<int>(pkzo::Key::PAGEDOWN);
    io.KeyMap[ImGuiKey_Home]        = static_cast<int>(pkzo::Key::HOME);
    io.KeyMap[ImGuiKey_End]         = static_cast<int>(pkzo::Key::END);
    io.KeyMap[ImGuiKey_Insert]      = static_cast<int>(pkzo::Key::INSERT);
    io.KeyMap[ImGuiKey_Delete]      = static_cast<int>(pkzo::Key::DELETE);
    io.KeyMap[ImGuiKey_Backspace]   = static_cast<int>(pkzo::Key::BACKSPACE);
    io.KeyMap[ImGuiKey_Space]       = static_cast<int>(pkzo::Key::SPACE);
    io.KeyMap[ImGuiKey_Enter]       = static_cast<int>(pkzo::Key::RETURN);
    io.KeyMap[ImGuiKey_Escape]      = static_cast<int>(pkzo::Key::ESCAPE);
    io.KeyMap[ImGuiKey_KeyPadEnter] = static_cast<int>(pkzo::Key::KP_ENTER);
    io.KeyMap[ImGuiKey_A]           = static_cast<int>(pkzo::Key::A);
    io.KeyMap[ImGuiKey_C]           = static_cast<int>(pkzo::Key::C);
    io.KeyMap[ImGuiKey_V]           = static_cast<int>(pkzo::Key::V);
    io.KeyMap[ImGuiKey_X]           = static_cast<int>(pkzo::Key::X);
    io.KeyMap[ImGuiKey_Y]           = static_cast<int>(pkzo::Key::Y);
    io.KeyMap[ImGuiKey_Z]           = static_cast<int>(pkzo::Key::Z);

    io.SetClipboardTextFn = ImGui_ImplPkzo_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplPkzo_GetClipboardText;
    io.ClipboardUserData  = nullptr;

    return true;
}

void ImGui_ImplPkzo_Shutdown()
{
    if (g_clipboard_data)
    {
        SDL_free(g_clipboard_data);
        g_clipboard_data = nullptr;
    }
}

void ImGui_ImplPkzo_HandleMouseButtonDown(pkzo::MouseButton button, glm::ivec2 pos)
{
    auto& io = ImGui::GetIO();
    if (button == pkzo::MouseButton::LEFT)
    {
        io.MouseDown[0] = true;
    }
    if (button == pkzo::MouseButton::MIDDLE)
    {
        io.MouseDown[1] = true;
    }
    if (button == pkzo::MouseButton::RIGHT)
    {
        io.MouseDown[0] = true;
    }
    io.MousePos = ImVec2(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void ImGui_ImplPkzo_HandleMouseButtonUp(pkzo::MouseButton button, glm::ivec2 pos)
{
    auto& io = ImGui::GetIO();
    if (button == pkzo::MouseButton::LEFT)
    {
        io.MouseDown[0] = false;
    }
    if (button == pkzo::MouseButton::MIDDLE)
    {
        io.MouseDown[1] = false;
    }
    if (button == pkzo::MouseButton::RIGHT)
    {
        io.MouseDown[0] = false;
    }
    io.MousePos = ImVec2(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void ImGui_ImplPkzo_HandleMouseMove(glm::ivec2 pos, glm::ivec2 rel)
{
    auto& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void ImGui_ImplPkzo_HandleMouseWheel(glm::ivec2 rel)
{
    auto& io = ImGui::GetIO();
    io.MouseWheelH += rel.x;
    io.MouseWheel  += rel.y;
}

void ImGui_ImplPkzo_HandleKeyDown(pkzo::KeyMod mod, pkzo::Key key)
{
    auto& io = ImGui::GetIO();
    auto ikey = static_cast<int>(key);
    if (ikey >= 0 && ikey < IM_ARRAYSIZE(io.KeysDown))
    {
        io.KeysDown[ikey] = true;
        io.KeyShift = ((mod & pkzo::KeyMod::SHIFT) != pkzo::KeyMod::NONE);
        io.KeyCtrl  = ((mod & pkzo::KeyMod::CTRL)  != pkzo::KeyMod::NONE);
        io.KeyAlt   = ((mod & pkzo::KeyMod::ALT)   != pkzo::KeyMod::NONE);
        io.KeySuper = ((mod & pkzo::KeyMod::GUI)   != pkzo::KeyMod::NONE);
    }
}

void ImGui_ImplPkzo_HandleKeyUp(pkzo::KeyMod mod, pkzo::Key key)
{
    ImGuiIO& io = ImGui::GetIO();
    auto ikey = static_cast<int>(key);
    if (ikey >= 0 && ikey < IM_ARRAYSIZE(io.KeysDown))
    {
        io.KeysDown[ikey] = false;
        io.KeyShift = ((mod & pkzo::KeyMod::SHIFT) != pkzo::KeyMod::NONE);
        io.KeyCtrl  = ((mod & pkzo::KeyMod::CTRL)  != pkzo::KeyMod::NONE);
        io.KeyAlt   = ((mod & pkzo::KeyMod::ALT)   != pkzo::KeyMod::NONE);
        io.KeySuper = ((mod & pkzo::KeyMod::GUI)   != pkzo::KeyMod::NONE);
    }
}

void ImGui_ImplPkzo_HandleText(const std::string_view text)
{
    auto& io = ImGui::GetIO();
    io.AddInputCharactersUTF8(text.data());
}

auto g_last_frame = std::chrono::steady_clock::now();

void ImGui_ImplPkzo_NewFrame(glm::uvec2 size, glm::uvec2 draw_size)
{
    using fsec = std::chrono::duration<float>;

    auto& io = ImGui::GetIO();
    IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer back-end. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

    io.DisplaySize = ImVec2(static_cast<float>(size.x), static_cast<float>(size.y));
    io.DisplayFramebufferScale = ImVec2(static_cast<float>(draw_size.x / size.x), static_cast<float>(draw_size.y / size.y));

    auto now = std::chrono::steady_clock::now();
    io.DeltaTime = std::chrono::duration_cast<fsec>(now - g_last_frame).count();
    g_last_frame = now;
}
