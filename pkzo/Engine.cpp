// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.


#include "Engine.h"

#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "dbg.h"
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"

namespace pkzo
{
    Engine::Engine(const std::string_view i)
    : id{i}
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) < 0)
        {
            throw std::runtime_error(IMG_GetError());
        }
        if (TTF_Init() < 0)
        {
            throw std::runtime_error(TTF_GetError());
        }

        // TODO load settings

        window   = std::make_unique<Window>(glm::uvec2(800, 600), Window::STATIC, id);
        window->on(Window::DRAW, [this] () {
            draw();
        });

        mouse    = std::make_unique<Mouse>();
        keyboard = std::make_unique<Keyboard>();
    }

    Engine::~Engine()
    {
        screen = nullptr;
        camera = nullptr;
        scene = nullptr;
        keyboard = nullptr;
        mouse = nullptr;
        window = nullptr;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    const std::string& Engine::get_id() const
    {
        return id;
    }

    Window& Engine::get_window()
    {
        PKZO_ASSERT(window);
        return *window;
    }

    const Window& Engine::get_window() const
    {
        PKZO_ASSERT(window);
        return *window;
    }

    Mouse& Engine::get_mouse()
    {
        PKZO_ASSERT(mouse);
        return *mouse;
    }

    const Mouse& Engine::get_mouse() const
    {
        PKZO_ASSERT(mouse);
        return *mouse;
    }

    Keyboard& Engine::get_keyboard()
    {
        PKZO_ASSERT(keyboard);
        return *keyboard;
    }

    const Keyboard& Engine::get_keyboard() const
    {
        PKZO_ASSERT(keyboard);
        return *keyboard;
    }

    void Engine::set_screen(std::shared_ptr<Screen> value)
    {
        screen = std::move(value);
    }

    std::shared_ptr<Screen> Engine::get_screen() const
    {
        return screen;
    }

    void Engine::set_scene(std::shared_ptr<Scene> value)
    {
        scene = std::move(value);
    }

    std::shared_ptr<Scene> Engine::get_scene() const
    {
        return scene;
    }

    void Engine::set_camera(std::shared_ptr<Camera> value)
    {
        camera = std::move(value);
    }

    std::shared_ptr<Camera> Engine::get_camera() const
    {
        return camera;
    }

    int Engine::run()
    {
        running = true;
        while (running)
        {
            handle_events();
            tick();
            get_window().draw();
        }
        return 0;
    }

    void Engine::stop()
    {
        running = false;
    }

    void Engine::tick()
    {
    }

    void Engine::handle_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
             switch (event.type)
             {
                case SDL_QUIT:
                    get_window().handle_event(event);
                    stop();
                    break;
                case SDL_WINDOWEVENT:
                    get_window().handle_event(event);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    get_keyboard().handle_event(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    get_mouse().handle_event(event);
                    break;
                default:
                    /* stfu */
                    break;
             }
        }
    }

    void Engine::draw()
    {
        if (scene && camera)
        {
            camera->set_resolution(window->get_size());
            scene->draw(*camera);
        }

        if (screen)
        {
            screen->draw();
        }
    }

    void show_error_dialog(const std::string_view title, const std::string_view message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.data(), message.data(), NULL);
    }
}