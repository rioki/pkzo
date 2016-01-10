//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#include "Window.h"

#include <set>
#include <SDL.h>
#include <gl/GLEW.h>


namespace pkzo
{
    unsigned int Window::get_display_count()
    {
        return SDL_GetNumVideoDisplays();
    }

    std::tuple<unsigned int, unsigned int> Window::get_display_resolution(unsigned int i)
    {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);

        return std::tuple<unsigned int, unsigned int>(mode.w, mode.h);
    }

    std::vector<std::tuple<unsigned int, unsigned int>>  Window::get_valid_sizes()
    {    
        std::set<std::tuple<unsigned int, unsigned int>> result;

        int modes = SDL_GetNumDisplayModes(0);
        if (modes == -1)
        {
            throw std::logic_error(SDL_GetError());
        }
        
        for (int i = 0; i < modes; i++)
        {
            SDL_DisplayMode mode;
            int r = SDL_GetDisplayMode(0, i, &mode);
            if (r != 0)
            {
                throw std::logic_error(SDL_GetError());
            }
            result.insert(std::make_tuple((unsigned int)mode.w, (unsigned int)mode.h));
        }
        
        // invert order 
        return std::vector<std::tuple<unsigned int, unsigned int>>(result.begin(), result.end());
    }
    
    Window::Window(unsigned int width, unsigned int height, Flags f)
    : window(nullptr), glcontext(nullptr), flags(f)
    {
        unsigned int sdl_flags = SDL_WINDOW_OPENGL;

        if (width == 0 && height == 0 && flags & FULLSCREEN)
        {
            sdl_flags = sdl_flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        else if (flags & FULLSCREEN)
        {
            sdl_flags = sdl_flags | SDL_WINDOW_FULLSCREEN;
        }
        if (flags & BORDERLESS)
        {
            sdl_flags = sdl_flags | SDL_WINDOW_BORDERLESS;
        }
        if (flags & RESIZABLE)
        {
            sdl_flags = sdl_flags | SDL_WINDOW_RESIZABLE;
        }

        window = SDL_CreateWindow("pkzo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdl_flags);
        if (window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }
    }

    Window::Window(unsigned int width, unsigned int height, bool fullscreen)
    : Window(width, height, fullscreen ? FULLSCREEN : NO_FLAGS) {}

    Window::~Window() 
    {
        if (glcontext != nullptr)
        {
            SDL_GL_DeleteContext(glcontext);
            glcontext = nullptr;
        }

        if (window != nullptr)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }

    void Window::change_video_mode(unsigned int width, unsigned int height, Flags f)
    {
        flags = f;

        SDL_SetWindowSize(window, width, height);
        
        if ((flags & FULLSCREEN) == FULLSCREEN)
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        }
        else
        {
            SDL_SetWindowFullscreen(window, 0);
        }

        if ((flags & BORDERLESS) == BORDERLESS)
        {
            SDL_SetWindowBordered(window, SDL_FALSE);
        }
        else
        {
            SDL_SetWindowBordered(window, SDL_TRUE);
        }
    }

    unsigned int Window::get_width() const
    {
        int w;
        SDL_GetWindowSize(window, &w, nullptr);
        return w;
    }

    unsigned int Window::get_height() const
    {
        int h;
        SDL_GetWindowSize(window, nullptr, &h);
        return h;
    }

    bool Window::is_fullscreen() const
    {
        return (flags & FULLSCREEN) == FULLSCREEN;
    }

    bool Window::is_borderless() const
    {
        return (flags & BORDERLESS) == BORDERLESS;
    }

    bool Window::is_resizable() const
    {
        return (flags & RESIZABLE) == RESIZABLE;
    }

    void Window::set_title(const std::string& value)
    {
        SDL_SetWindowTitle(window, value.c_str());
    }

    std::string Window::get_title() const
    {
        const char* title = SDL_GetWindowTitle(window);
        return title != nullptr ? std::string(title) : std::string();
    }

    void Window::on_draw(std::function<void()> cb)
    {
        draw_cb = cb;
    }

    void Window::draw() 
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        glViewport(0, 0, w, h);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (draw_cb)
        {
            draw_cb();
        }

        SDL_GL_SwapWindow(window);
    }
}
