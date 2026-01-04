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

#include "Window.h"

#include <SDL3/SDL.h>

#include "tinyformat.h"

namespace pkzo
{
    std::vector<Window*> Window::instances;

    auto get_window_flags(Api api)
    {
        using enum Api;

        switch (api)
        {
            case OPENGL:
                return SDL_WINDOW_OPENGL;
            default:
                std::unreachable();
        }
    }

    auto get_window_flags(WidnowState state)
    {
        using enum WidnowState;

        switch (state)
        {
            case WINDOW:
                return 0ULL;
            case FULLSCREEN:
                return SDL_WINDOW_FULLSCREEN;
            case MINIMIZED:
                return SDL_WINDOW_MINIMIZED;
            case MAXIMIZED:
                return SDL_WINDOW_MAXIMIZED;
            default:
                std::unreachable();
        }
    }


    auto get_window_flags(WindowMode mode)
    {
        using enum WindowMode;

        auto result = 0ULL;

        if ((mode & RESIZABLE)     == RESIZABLE)     result |= SDL_WINDOW_RESIZABLE;
        if ((mode & BORDERLESS)    == BORDERLESS)    result |= SDL_WINDOW_BORDERLESS;
        if ((mode & TRANSPARENT)   == TRANSPARENT)   result |= SDL_WINDOW_TRANSPARENT;
        if ((mode & MODAL)         == MODAL)         result |= SDL_WINDOW_MODAL;
        if ((mode & ALWAYS_ON_TOP) == ALWAYS_ON_TOP) result |= SDL_WINDOW_ALWAYS_ON_TOP;
        if ((mode & HIDDEN)        == HIDDEN)        result |= SDL_WINDOW_HIDDEN;
        if ((mode & UTILITY)       == UTILITY)       result |= SDL_WINDOW_UTILITY;
        if ((mode & TOOLTIP)       == TOOLTIP)       result |= SDL_WINDOW_TOOLTIP;
        if ((mode & POPUP_MENU)    == POPUP_MENU)    result |= SDL_WINDOW_POPUP_MENU;

        return result;
    }

    int get_opengl_profile(const std::string& id)
    {
        if (id == "core")
        {
            return SDL_GL_CONTEXT_PROFILE_CORE;
        }
        else if (id == "compatibility")
        {
            return SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
        }
        else if (id == "es")
        {
            return SDL_GL_CONTEXT_PROFILE_ES;
        }
        else
        {
            throw std::invalid_argument(tfm::format("Unknown OpenGL profile: %s.", id));
        }
    }

    Window::Window(Init init)
    : api(init.api)
    {
        instances.push_back(this);

        auto flags = get_window_flags(init.api)
                   | get_window_flags(init.state)
                   | get_window_flags(init.mode);
        window = SDL_CreateWindow(init.title.data(), init.size.x, init.size.y, flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        switch (init.api)
        {
            case Api::OPENGL:
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, init.api_version.x);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, init.api_version.y);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                glcontext = SDL_GL_CreateContext(window);
                if (glcontext == nullptr)
                {
                    throw std::runtime_error(SDL_GetError());
                }
            break;
        }
    }

    Window::~Window()
    {
        switch (api)
        {
            case Api::OPENGL:
                SDL_GL_DestroyContext(glcontext);
            break;
        }
        SDL_DestroyWindow(window);

        std::erase(instances, this);
    }

    void Window::draw()
    {
        switch (api)
        {
            case Api::OPENGL:
                SDL_GL_SwapWindow(window);
            break;
        }
    }
}
