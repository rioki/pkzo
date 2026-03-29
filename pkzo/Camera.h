// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Scene.h"

#include <optional>

namespace pkzo
{
    class Scene;

    class PKZO_EXPORT Camera : public SceneNode
    {
    public:
        struct Init
        {
            Node*      parent     = nullptr;
            glm::mat4  transform  = glm::mat4(1.0f);
            float      fov        = 70.0f;
            float      distance   = 1000.0f;
            glm::uvec2 resolution = glm::uvec2(800u, 600u);
        };

        Camera(Init init);

        ~Camera();

        void set_fov(float value);
        float get_fov() const;

        void set_distance(float value);
        float get_distance() const;

        void set_resolution(glm::uvec2 value);
        glm::uvec2 get_resolution() const;

        glm::mat4 get_projection_matrix() const;
        glm::mat4 get_view_matrix() const;

    private:
        float      fov;
        float      distance;
        glm::uvec2 resolution;

        mutable std::optional<glm::mat4> projection_matrix_cache;
        mutable std::optional<glm::mat4> view_matrix_cache;
    };
}
