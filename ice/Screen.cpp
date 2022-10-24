// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "Screen.h"

#include "Engine.h"
#include "GraphicSystem.h"
#include "Renderer.h"
#include "HitArea.h"

namespace ice
{
    Screen::Screen()
    : Screen({800, 600}) {}

    Screen::Screen(const glm::vec2& _size)
    : size(_size)
    {
        assert(size.x > 0.0f && size.y > 0.0f);
    }

    const glm::vec2& Screen::get_size() const noexcept
    {
        return size;
    }

    void Screen::resize(const glm::vec2& value) noexcept
    {
        assert(value.x > 0.0f && value.y > 0.0f);
        size = value;
        if (renderer)
        {
            renderer->update_camera_ortho_size(camera_handle, glm::vec2(size));
        }
    }

    Renderer* Screen::get_renderer() noexcept
    {
        return renderer;
    }

    const Renderer* Screen::get_renderer() const noexcept
    {
        return renderer;
    }

    void Screen::draw()
    {
        if (renderer)
        {
            renderer->render();
        }
    }

    void Screen::activate()
    {
        auto engine = get_engine();
        assert(engine != nullptr);

        if (auto gs = engine->get_system<GraphicSystem>())
        {
            renderer = gs->create_renderer(RendererType::UNLIT);
            auto ct = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 1.0f));
            camera_handle = renderer->add_ortho_camera(ct, glm::vec2(size), size);
        }
        NodeRoot<Screen>::activate();
    }

    void Screen::deactivate()
    {
        NodeRoot<Screen>::deactivate();
        if (renderer)
        {
            auto engine = get_engine();
            assert(engine != nullptr);

            auto gs = engine->get_system<GraphicSystem>();
            assert(gs);
            gs->release_renderer(renderer);
            renderer = nullptr;
        }
    }

    void Screen::handle_mouse_down(const MouseButton button, const glm::vec2& pos)
    {
        for (const auto& ha : hitareas)
        {
            assert(ha != nullptr);
            ha->handle_mouse_down(button, pos);
        }
    }

    void Screen::handle_mouse_up(const MouseButton button, const glm::vec2& pos)
    {
        for (const auto& ha : hitareas)
        {
            assert(ha != nullptr);
            ha->handle_mouse_up(button, pos);
        }
    }

    void Screen::add_hitarea(HitArea* ha)
    {
        hitareas.push_back(ha);
    }

    void Screen::remove_hitarea(HitArea* ha)
    {
        auto i = find(begin(hitareas), end(hitareas), ha);
        assert(i != end(hitareas));
        hitareas.erase(i);
    }

    template <typename T>
    T map(T source_left, T source_right, T target_left, T target_right, T value)
    {
        auto source_range = source_right - source_left;
        auto target_range = target_right - target_left;
        return (value - source_left) * (target_range / source_range) + target_left;
    }

    glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos)
    {
        auto hss = screen_size / 2.0f;
        return {
            map<float>(0.0f, win_size.x, -hss.x,  hss.x, pos.x),
            map<float>(0.0f, win_size.y,  hss.y, -hss.y, pos.y)
        };
    }
}
