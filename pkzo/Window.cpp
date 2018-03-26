// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
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

#include <SDL.h>
#include <GL/glew.h>

namespace pkzo
{
    std::vector<Window*> Window::instances;

    Window::Window(rgm::ivec2 size, Mode m)
    : mode(m)
    {
        instances.push_back(this);
        
        unsigned int flags = SDL_WINDOW_OPENGL;
        switch (mode)
        {
            case STATIC:
                flags = SDL_WINDOW_OPENGL;
                break;
            case RESIZABLE:
                flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
                break;
            case FULLSCREEN:
                flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
                break;
        }

        window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size[0], size[1], flags);
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

        auto i = std::find(instances.begin(), instances.end(), this);
        if (i != instances.end())
        {
            instances.erase(i);
        }
    }

   rgm::ivec2 Window::get_size() const
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return rgm::ivec2(w, h);
    }

    float Window::get_aspect() const
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return (float)w / (float)h;
    }

    Window::Mode Window::get_mode() const
    {
        return mode;
    }

    void Window::on_draw(std::function<void ()> cb)
    {
        draw_cb = cb;
    }

    void Window::on_resize(std::function<void (rgm::ivec2)> cb)
    {
        resize_cb = cb;
    }

    void Window::on_close(std::function<void ()> cb)
    {
        close_cb = cb;
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

    bool Window::handle_event(SDL_Event& event)
    {
        bool handled = false;
        switch (event.type)
        {
            case SDL_QUIT:
                if (close_cb)
                {
                    close_cb();
                    handled = true;
                }
                break;
            case SDL_WINDOWEVENT:            
                if (event.window.windowID == SDL_GetWindowID(window))  
                {
                    switch (event.window.event)  
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:  
                        {
                            if (resize_cb)
                            {
                                int width = event.window.data1;
                                int height = event.window.data2;
                                resize_cb(rgm::ivec2(width, height));
                                handled = true;
                            }
                            break;
                        }
                        default:
                            // STFU
                            break;
                    }
                }
                break;   
            default:
                // STFU
                break;
        } 

        return handled;
    }
}
