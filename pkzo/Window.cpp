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

#include "functions.h"
#include "Window.h"

#include <SDL.h>
#include <gl/GLEW.h>

namespace pkzo
{
    Window::Window(unsigned int width, unsigned int height, Flags flags)
    : window(nullptr), glcontext(nullptr)
    {
        init();    

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

        if (draw_cb)
        {
            draw_cb();
        }

        SDL_GL_SwapWindow(window);
    }
}
