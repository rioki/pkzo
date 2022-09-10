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

#pragma once
#include "config.h"

#include <string>
#include <iostream>
#include <string_view>
#include <glm/glm.hpp>
#include <rsig/rsig.h>

#include "utils.h"
#include "SdlSentry.h"

struct SDL_Window;
typedef void *SDL_GLContext;

namespace ice
{
    enum class WindowMode
    {
        STATIC,
        RESIZABLE,
        FULLSCREEN,
        NATIVE_FULLSCREEN
    };

    ICE_SERIALIZE_ENUM(WindowMode, {
                                     {WindowMode::STATIC, "STATIC"},
                                     {WindowMode::RESIZABLE, "RESIZABLE"},
                                     {WindowMode::FULLSCREEN, "FULLSCREEN"},
                                     {WindowMode::NATIVE_FULLSCREEN, "NATIVE_FULLSCREEN"}
                                   });


    class ICE_EXPORT Window
    {
    public:
        Window(const glm::uvec2& size, WindowMode mode, const std::string_view caption);
        Window(const Window&) = delete;
        ~Window();
        Window& operator = (const Window&) = delete;

        void set_caption(const std::string_view text) noexcept;
        std::string get_caption() const noexcept;

        void resize(const glm::uvec2& size, WindowMode flags);
        glm::uvec2 get_size() const noexcept;
        WindowMode get_mode() const noexcept;

        rsig::signal<>& get_draw_sginal() noexcept;
        rsig::connection on_draw(const std::function<void ()>& cb) noexcept;

        void draw() const noexcept;

    private:
        SdlSentry     sdl_sentry;

        SDL_Window*   window    = nullptr;
        SDL_GLContext glcontext = nullptr;

        rsig::signal<> draw_signal;
    };
}
