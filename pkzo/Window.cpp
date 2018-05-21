
#include "Window.h"

#include <SDL.h>
#include <SDL_opengl.h>

namespace pkzo
{
    std::vector<Window*> Window::instances;

    Window::Window(const rgm::uvec2& size, Mode m, const std::string& title)
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

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size[0], size[1], flags);
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

    rgm::uvec2 Window::get_size() const
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return rgm::uvec2(w, h);
    }

    Window::Mode Window::get_mode() const
    {
        return mode;
    }

    void Window::set_title(const std::string& value)
    {
        SDL_SetWindowTitle(window, value.c_str());
    }

    std::string Window::get_title() const
    {
        const char* title = SDL_GetWindowTitle(window);
        if (title != nullptr)
        {
            return std::string(title);
        }
        else
        {
            return std::string();
        }
    }

    void Window::on_draw(std::function<void ()> cb)
    {
        draw_cb = cb;
    }

    void Window::on_resize(std::function<void (unsigned int, unsigned int)> cb)
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

    void Window::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                if (close_cb)
                {
                    close_cb();
                }
                break;
            case SDL_WINDOWEVENT:            
                if (event.window.windowID == SDL_GetWindowID(window))  
                {
                    switch (event.window.event)  
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:  
                        {
                            int width = event.window.data1;
                            int height = event.window.data2;
                            if (resize_cb)
                            {
                                resize_cb(width, height);
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
    }
}
