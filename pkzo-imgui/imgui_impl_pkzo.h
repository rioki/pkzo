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

#pragma once

#include <imgui.h>

#include <pkzo/Mouse.h>
#include <pkzo/Keyboard.h>

IMGUI_IMPL_API bool ImGui_ImplPkzo_Init();
IMGUI_IMPL_API void ImGui_ImplPkzo_Shutdown();

IMGUI_IMPL_API void ImGui_ImplPkzo_HandleMouseButtonDown(pkzo::MouseButton button, glm::ivec2 pos);
IMGUI_IMPL_API void ImGui_ImplPkzo_HandleMouseButtonUp(pkzo::MouseButton button, glm::ivec2 pos);
IMGUI_IMPL_API void ImGui_ImplPkzo_HandleMouseMove(glm::ivec2 pos, glm::ivec2 rel);
IMGUI_IMPL_API void ImGui_ImplPkzo_HandleMouseWheel(glm::ivec2 rel);

IMGUI_IMPL_API void ImGui_ImplPkzo_HandleKeyDown(pkzo::KeyMod mod, pkzo::Key key);
IMGUI_IMPL_API void ImGui_ImplPkzo_HandleKeyUp(pkzo::KeyMod mod, pkzo::Key key);
IMGUI_IMPL_API void ImGui_ImplPkzo_HandleText(const std::string_view text);

IMGUI_IMPL_API void ImGui_ImplPkzo_NewFrame(glm::uvec2 size, glm::uvec2 draw_size);

