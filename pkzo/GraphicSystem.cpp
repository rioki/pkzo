// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "GraphicSystem.h"

#include <cassert>
#include <SDL2/SDL.h>

#include "Engine.h"
#include "Window.h"
#include "DebugDrawer.h"
#include "RenderQueue.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"

namespace pkzo
{
    GraphicSystem::GraphicSystem(Engine& e)
    : engine(e)
    {
        window = std::make_shared<Window>(glm::uvec2(1600, 900), Window::STATIC, engine.get_id());
        window->on(Window::DRAW, [this] () {
            draw();
        });
        render_queue = std::make_unique<RenderQueue>(window->get_size());

        #ifdef _DEBUG
        engine.start_system<DebugDrawer>();
        #endif
    }

    GraphicSystem::~GraphicSystem() = default;

    std::shared_ptr<Window> GraphicSystem::get_window()
    {
        assert(window);
        return window;
    }

    void GraphicSystem::tick(float dt)
    {
        assert(window);
        window->draw();
    }

    void GraphicSystem::draw()
    {
        auto scene = engine.get_scene();
        auto camera = engine.get_camera();

        if (scene && camera)
        {
            scene->draw(*camera, *render_queue);
        }

        auto dd = engine.get_system<DebugDrawer>();
        if (dd && camera)
        {
            dd->draw(*camera);
        }

        auto screen = engine.get_screen();
        if (screen)
        {
            screen->draw(*render_queue);
        }
    }
}
