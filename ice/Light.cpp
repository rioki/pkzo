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
#include "Light.h"

#include "SceneRenderer.h"

namespace ice
{
    Light::Light() noexcept
    : Light(glm::mat4(1.0f)) {}

    Light::Light(const glm::mat4& _transform) noexcept
    : SceneNode(_transform)
    {
        on_move([this] ()
        {
            if (renderer)
            {
                renderer->update_light_transform(render_handle, get_world_transform());
            }
        });
    }

    void Light::activate()
    {
        assert(renderer == nullptr);
        auto scene = get_root();
        assert(scene != nullptr);
        if (renderer = scene->get_renderer())
        {
            render_handle = register_light(*renderer);
        }
    }

    void Light::deactivate()
    {
        if (renderer != nullptr)
        {
            renderer->remove_light(render_handle);
            renderer      = nullptr;
            render_handle = 0;
        }
    }
}
