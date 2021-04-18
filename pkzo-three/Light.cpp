//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "Light.h"

#include "Scene.h"

namespace pkzo::three
{
    Light::Light(const glm::mat4& transform) noexcept
    : SceneNode(transform) {}

    void Light::on_attach_scene(Scene* scene) noexcept
    {
        SceneNode::on_attach_scene(scene);
        pipeline = scene->get_render_pipeline();
        pipeline_handle = pipeline->add_light(get_parameters());
    }

    void Light::on_detach_scene() noexcept
    {
        pipeline->remove_light(pipeline_handle);
        pipeline        = nullptr;
        pipeline_handle = 0;
        SceneNode::on_detach_scene();
    }
}