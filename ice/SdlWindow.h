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

#include <rsig/rsig.h>

#include "Window.h"

namespace ice
{


    class ICE_EXPORT SdlWindow : public Window
    {
    public:
        SdlWindow(const glm::uvec2& size, WindowMode mode, const std::string_view caption);
        ~SdlWindow();

        void set_caption(const std::string_view text) noexcept override;
        std::string get_caption() const noexcept override;

        void resize(const glm::uvec2& size, WindowMode flags) override;
        glm::uvec2 get_size() const noexcept override;
        WindowMode get_mode() const noexcept override;

        rsig::signal<>& get_draw_sginal() noexcept;
        rsig::connection on_draw(const std::function<void ()>& cb) noexcept;

        void draw() const noexcept;

    private:
        SdlSentry     sdl_sentry;

        SDL_Window*   window    = nullptr;
        SDL_GLContext glcontext = nullptr;

        rsig::signal<> draw_signal;;
    };


}
