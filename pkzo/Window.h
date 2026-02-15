// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include <functional>

#include <glm/glm.hpp>
#include <rsig/rsig.h>
#include <SDL3/SDL.h>

#include "api.h"
#include "SdlSentry.h"
#include "GraphicContext.h"

namespace pkzo
{
    enum class WindowState : Uint64
    {
        WINDOW     = 0ULL,
        FULLSCREEN = SDL_WINDOW_FULLSCREEN,
        MINIMIZED  = SDL_WINDOW_MINIMIZED,
        MAXIMIZED  = SDL_WINDOW_MAXIMIZED
    };

    class PKZO_EXPORT Window
    {
    public:
        static void route_event(const SDL_Event& event);

        struct Init
        {
            std::string title = "Pkzo";
            glm::uvec2  size  = glm::uvec2(800u, 600u);
            WindowState state = WindowState::WINDOW;
            Api         api   = Api::OPENGL;
        };

        Window(Init init);

        ~Window();

        glm::uvec2 get_size() const;

        void set_size(const glm::uvec2& value);

        glm::uvec2 get_resolution() const;

        WindowState get_state() const;

        bool get_fullscreen() const;

        void set_fullscreen(bool value);

        void capture_mouse();
        void release_mouse();

        rsig::connection on_draw(const std::function<void (GraphicContext&)>& handler);

        void draw();

    private:
        static std::vector<Window*> instances;

        SdlSentry                       sdl_sentry = SdlSentry{SdlSubsystem::VIDEO | SdlSubsystem::EVENTS};
        SDL_Window*                     window     = nullptr;
        std::unique_ptr<GraphicContext> graphic_context;

        rsig::signal<GraphicContext&> draw_signal;

        Window(const Window&) = delete;
        Window& operator = (const Window&) = delete;
    };
}
