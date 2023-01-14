// pkzo
// Copyright 2022-2023 Sean Farrell
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

#include "SceneNode.h"

namespace pkzo
{
    class Renderer;

    class ICE_EXPORT Camera : public SceneNode
    {
    public:
        Camera() noexcept;

        Camera(const glm::mat4& transform, const float fov, const glm::uvec2 resolution) noexcept;

        float get_fov() const noexcept;
        void set_fov(const float value) noexcept;

        glm::uvec2 get_resolution() const noexcept;
        void set_resolution(const glm::uvec2 value) noexcept;

        void activate() override;
        void deactivate() override;

    private:
        float      fov        = 90.0f; // horizontal full range FOV
        glm::uvec2 resolution = {1600, 900};

        Renderer* renderer = nullptr;
        unsigned int render_handle = 0;
    };
}
