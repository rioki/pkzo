#pragma once
class MockGraphicSystem
{
};


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

#include <gmock/gmock.h>

#include <ice/GraphicSystem.h>

namespace ice::test
{
    class ICE_EXPORT MockGraphicSystem : public GraphicSystem
    {
    public:
        MockGraphicSystem(Engine& e)
        : GraphicSystem(e) {}

        ~MockGraphicSystem() = default;

        MOCK_METHOD(Window*, get_window, (), (noexcept));
        MOCK_METHOD(const Window*, get_window, (), (const, noexcept));

        MOCK_METHOD(const glm::uvec2, get_window_size, (), (const, noexcept));

        MOCK_METHOD(std::shared_ptr<Texture>, get_screenshot, (), (const, noexcept));

        MOCK_METHOD(ScreenRenderer*, create_screen_renderer, (), (noexcept));
        MOCK_METHOD(void, release_screen_renderer, (ScreenRenderer* renderer), (noexcept));

        MOCK_METHOD(SceneRenderer*, create_scene_renderer, (), (noexcept));
        MOCK_METHOD(void, release_scene_renderer, (SceneRenderer* renderer), (noexcept));
    };
}
