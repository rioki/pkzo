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
#include "SdlGraphicSystem.h"

#include "utils.h"
#include "glm_json.h"

#include "Engine.h"
#include "OpenGLRenderer.h"
#include "OpenGLVideoMemory.h"
#include "Scene.h"
#include "Screen.h"
#include "SdlWindow.h"
#include "Settings.h"
#include "Texture.h"

namespace ice
{
    SdlGraphicSystem::SdlGraphicSystem(Engine& e)
    : GraphicSystem(e)
    {
        const auto& settings = engine.get_settings();

        auto resolution = settings.get_value("GraphicSystem", "resolution", glm::vec2(800, 600));
        #if DEBUG
        auto mode = settings.get_value("GraphicSystem", "mode", WindowMode::STATIC);
        #else
        auto mode = settings.get_value("GraphicSystem", "mode", WindowMode::NATIVE_FULLSCREEN);
        #endif

        window = std::make_unique<SdlWindow>(resolution, mode, "Ice Engine");
        window->on_draw(rsig::mem_fun(this, &SdlGraphicSystem::render_frame));

        vmem = std::make_unique<OpenGLVideoMemory>();
    }

    SdlGraphicSystem::~SdlGraphicSystem()
    {
        soft_assert(renderers.empty());
        renderers.clear();
        vmem   = nullptr;
        window = nullptr;
    }

    Window* SdlGraphicSystem::get_window() noexcept
    {
        assert(window);
        return window.get();
    }

    const Window* SdlGraphicSystem::get_window() const noexcept
    {
        assert(window);
        return window.get();
    }

    const glm::uvec2 SdlGraphicSystem::get_window_size() const noexcept
    {
        if (window)
        {
            return window->get_size();
        }
        else
        {
            return glm::uvec2(0u);
        }
    }

    Renderer* SdlGraphicSystem::create_renderer(RendererType type) noexcept
    {
        assert(vmem);
        return add_unique_ptr<OpenGLRenderer>(renderers, *vmem, type);
    }

    void SdlGraphicSystem::release_renderer(Renderer* renderer) noexcept
    {
        remove_unique_ptr(renderers, renderer);
    }

    void SdlGraphicSystem::tick()
    {
        assert(window);
        window->draw();

        assert(vmem);
        vmem->collect();
    }

    std::shared_ptr<Texture> SdlGraphicSystem::get_screenshot() const noexcept
    {
        auto s = window->get_size();
        std::vector<std::byte> buffer(s.x * s.y * 3);
        glReadPixels(0, 0, s.x, s.y, GL_BGR, GL_UNSIGNED_BYTE, buffer.data());
        return std::make_shared<Texture>(s, ColorMode::RGB, DataType::UINT8, buffer.data(), "screen");
    }

    void SdlGraphicSystem::render_frame() noexcept
    {
        const auto scene = engine.get_scene();
        if (scene)
        {
            scene->draw();
        }

        const auto& overlay = engine.get_overlay();
        if (overlay)
        {
            overlay->draw();
        }

        debug_draw_signal.emit();
    }
}
