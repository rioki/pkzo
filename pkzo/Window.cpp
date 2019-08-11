// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Window.h"

#include <stdexcept>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace pkzo
{
    void clear_gl_errors()
    {
        GLenum e;
        do
        {
            e = glGetError();
        }
        while (e != GL_NO_ERROR);
    }

    std::string get_gl_error()
    {
        std::string result;

        GLenum e = glGetError();
        switch (e)
        {
            case GL_NO_ERROR:
                result = "GL_NO_ERROR";
                break;
            case GL_INVALID_ENUM:
                result = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                result = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                result = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                result = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                result = "GL_OUT_OF_MEMORY";
                break;
            default:
                assert(false && "invalud id");
                break;
        }

        return result;
    }

    Window::Window(const glm::uvec2& size, Mode m, const std::string& title)
    : mode(m)
    {
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

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
        }
        clear_gl_errors();
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

    glm::uvec2 Window::get_size() const
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return glm::uvec2(w, h);
    }

    float Window::get_aspect() const
    {
        auto s = get_size();
        return static_cast<float>(s.x) / static_cast<float>(s.y);
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

    void Window::draw()
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);

        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        emit(Event::DRAW);

        SDL_GL_SwapWindow(window);
    }

    void Window::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                emit(Event::CLOSE);
                break;
            case SDL_WINDOWEVENT:
                if (event.window.windowID == SDL_GetWindowID(window))
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            emit(Event::RESIZE, glm::uvec2{event.window.data1, event.window.data2});
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }
}
