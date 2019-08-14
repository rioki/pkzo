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
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"
#include "GraphicSystem.h"
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

        start_system<GraphicSystem>();
        start_system<InputSystem>();
        start_system<PhysicSystem>();
    }

    Engine::~Engine()
    {
        screen = nullptr;
        camera = nullptr;
        scene = nullptr;
        next_screen = nullptr;
        next_camera = nullptr;
        next_scene = nullptr;
        systems.clear();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    const std::string& Engine::get_id() const
    {
        return id;
    }

    std::shared_ptr<Window> Engine::get_window()
    {
        auto gs = get_system<GraphicSystem>();
        if (gs)
        {
            return gs->get_window();
        }
        else
        {
            return nullptr;
        }
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
        next_screen = std::move(value);
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
        next_camera = nullptr;
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

        if (next_screen != screen)
        {
            screen = next_screen;
            emit(CHANGE_SCREEN);
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

    void show_error_dialog(const std::string_view title, const std::string_view message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.data(), message.data(), NULL);
    }
}