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

#include "pch.h"

#include "SkyBox.h"

#include "Scene.h"
#include "SceneRenderer.h"

namespace pkzo
{
    SkyBox::SkyBox(Init init)
    : Node({init.parent}),
      texture(init.texture), cubemap(init.cubemap)
    {
        auto renderer = get_root()->get_renderer();
        renderer->add(this);
    }

    SkyBox::~SkyBox()
    {
        auto renderer = get_root()->get_renderer();
        renderer->remove(this);
    }

    std::shared_ptr<pkzo::Texture> SkyBox::get_texture() const
    {
        return texture;
    }

    std::shared_ptr<pkzo::CubeMap> SkyBox::get_cubemap() const
    {
        return cubemap;
    }

    void SkyBox::set_cubemap(const std::shared_ptr<pkzo::CubeMap>& value)
    {
        cubemap = value;
    }
}
