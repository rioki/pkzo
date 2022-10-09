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

#include "GraphicSystem.h"

namespace ice
{
    class SdlWindow;
    class Texture;
    class OpenGLVideoMemory;
    class OpenGLRenderer;

    class ICE_EXPORT SdlGraphicSystem : public GraphicSystem
    {
    public:
        SdlGraphicSystem(Engine& e);
        ~SdlGraphicSystem();

        Window* get_window() noexcept override;
        const Window* get_window() const noexcept override;

        const glm::uvec2 get_window_size() const noexcept override;

        std::shared_ptr<Texture> get_screenshot() const noexcept override;

        Renderer* create_renderer(RendererType type) noexcept override;
        void release_renderer(Renderer* renderer) noexcept override;

        void tick() override;

    private:
        std::unique_ptr<SdlWindow> window;
        std::unique_ptr<OpenGLVideoMemory> vmem;
        std::vector<std::unique_ptr<OpenGLRenderer>> renderers;

        void render_frame() noexcept;
    };
}
