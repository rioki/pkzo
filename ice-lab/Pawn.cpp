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
#include "Pawn.h"

namespace lab
{
    auto camera_x_forward()
    {
        return ice::lookat(glm::vec3(0.0f), glm::vec3(1.0f, 0.0, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    auto safe_resolution(ice::Engine& engine)
    {
        auto window = engine.get_window();
        if (!window)
        {
            soft_assert(false && "No window.");
            return glm::uvec2(800, 600);
        }

        return window->get_size();
    }

    Pawn::Pawn(ice::Engine& _engine, const glm::mat4& transform)
    : ice::SceneNodeGroup(transform),
      engine(_engine),
      camera(camera_x_forward(), engine.get_setting("Pawn", "fov", 90.0f), safe_resolution(engine))
    {
        add_node(camera);
    }
}
