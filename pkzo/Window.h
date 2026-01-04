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
#include "config.h"

#include <functional>

#include <glm/glm.hpp>
#include <rsig/rsig.h>

#include "SdlSentry.h"

struct SDL_Window;
struct SDL_GLContextState;
typedef SDL_GLContextState* SDL_GLContext;

namespace pkzo
{
    enum class Api
    {
        OPENGL,
        // VULKAN,
        // METAL
    };

    enum class WidnowState
    {
        WINDOW,
        FULLSCREEN,
        MINIMIZED,
        MAXIMIZED
    };

    enum class WindowMode
    {
        NORMAL        = 0,
        RESIZABLE     = bit(0),
        BORDERLESS    = bit(1),
        TRANSPARENT   = bit(2),
        MODAL         = bit(3),
        ALWAYS_ON_TOP = bit(4),
        HIDDEN        = bit(5),
        UTILITY       = bit(6),
        TOOLTIP       = bit(7),
        POPUP_MENU    = bit(8),
    };

    class PKZO_API Window
    {
    public:
        struct Init
        {
            std::string title       = "Pkzo";
            glm::uvec2  size        = glm::uvec2(800u, 600u);
            WidnowState state       = WidnowState::WINDOW;
            WindowMode  mode        = WindowMode::NORMAL;
            Api         api         = Api::OPENGL;
            glm::uvec3  api_version = glm::uvec3(4,3,0);
            std::string api_profile = "core";
        };

        Window(Init init);

        ~Window();

        void draw();

    private:
        static std::vector<Window*> instances;

        SdlSentry     sdl_sentry = SdlSentry{SdlSubsystem::VIDEO | SdlSubsystem::EVENTS};
        Api           api;
        SDL_Window*   window     = nullptr;
        SDL_GLContext glcontext  = nullptr;

        Window(const Window&) = delete;
        Window& operator = (const Window&) = delete;

    friend void rotue_events();
    };
}
