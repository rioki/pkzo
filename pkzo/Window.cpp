
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

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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
