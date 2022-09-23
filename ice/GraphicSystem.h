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

#pragma once
#include "config.h"

#include <memory>
#include <rsig/rsig.h>

#include "System.h"

namespace ice
{
    class Window;
    class Texture;
    class ScreenRenderer;
    class SceneRenderer;

    class ICE_EXPORT GraphicSystem : public System
    {
    public:
        GraphicSystem(Engine& e);
        virtual ~GraphicSystem() = default;

        virtual Window* get_window() noexcept = 0;
        virtual const Window* get_window() const noexcept = 0;

        virtual const glm::uvec2 get_window_size() const noexcept = 0;

        virtual std::shared_ptr<Texture> get_screenshot() const noexcept = 0;

        virtual ScreenRenderer* create_screen_renderer() noexcept = 0;
        virtual void release_screen_renderer(ScreenRenderer* renderer) noexcept = 0;

        virtual SceneRenderer* create_scene_renderer() noexcept = 0;
        virtual void release_scene_renderer(SceneRenderer* renderer) noexcept = 0;

        rsig::connection debug_draw(const std::function<void ()>& cb) noexcept;
        rsig::signal<>& get_debug_draw_signal() noexcept;

    protected:
        rsig::signal<> debug_draw_signal;
    };
}
