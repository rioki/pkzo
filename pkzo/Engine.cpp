// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Engine.h"

#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "dbg.h"
#include "Window.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"
#include "RenderQueue.h"
#include "InputSystem.h"
#include "PhysicSystem.h"
#include "DebugDrawer.h"

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

        window   = std::make_unique<Window>(glm::uvec2(1600, 900), Window::STATIC, id);
        window->on(Window::DRAW, [this] () {
            draw();
        });
        render_queue = std::make_unique<RenderQueue>(window->get_size());

        start_system<InputSystem>();

        #ifdef _DEBUG
        start_system<DebugDrawer>();
        #endif

        start_system<PhysicSystem>();
    }

    Engine::~Engine()
    {
        screen = nullptr;
        camera = nullptr;
        scene = nullptr;
        next_camera = nullptr;
        next_scene = nullptr;
        render_queue = nullptr;
        window = nullptr;
        systems.clear();
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

    std::shared_ptr<Mouse> Engine::get_mouse()
    {
        auto is = get_system<InputSystem>();
        if (is)
        {
            return is->get_mouse();
        }
        else
        {
            return nullptr;
        }
    }

    std::shared_ptr<Keyboard> Engine::get_keyboard()
    {
        auto is = get_system<InputSystem>();
        if (is)
        {
            return is->get_keyboard();
        }
        else
        {
            return nullptr;
        }
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
        next_scene = std::move(value);
        if (next_scene)
        {
            next_scene->engine = this;
        }
    }

    std::shared_ptr<Scene> Engine::get_scene() const
    {
        return scene;
    }

    void Engine::set_camera(std::shared_ptr<Camera> value)
    {
        next_camera = std::move(value);
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
        using fsec = std::chrono::duration<float>;

        auto now = std::chrono::steady_clock::now();
        auto dt = fsec(now - last_tick).count();
        last_tick = now;

        if (next_scene != scene)
        {
            if (scene)
            {
                scene->deactivate();
            }
            camera = nullptr;
            scene = next_scene;
            emit(CHANGE_SCENE);
            if (scene)
            {
                scene->activate();
            }
        }

        if (next_camera != camera)
        {
            camera = next_camera;
            emit(CHANGE_CAMERA);
        }

        for (auto& system : systems)
        {
            system->tick(dt);
        }

        if (scene)
        {
            scene->update(dt);
        }
    }

    void Engine::draw()
    {
        if (scene && camera)
        {
            scene->draw(*camera, *render_queue);
        }

        auto dd = get_system<DebugDrawer>();
        if (dd)
        {
            dd->draw(*camera);
        }

        if (screen)
        {
            screen->draw(*render_queue);
        }
    }

    void show_error_dialog(const std::string_view title, const std::string_view message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.data(), message.data(), NULL);
    }
}