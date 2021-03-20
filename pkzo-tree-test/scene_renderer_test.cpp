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

TEST(SceneRenderer, empty_scene)
{
    pkzo::Window window({800, 600}, pkzo::WindowMode::STATIC, __FUNCTION__);

    pkzo::three::Scene scene;

    auto camera = std::make_shared<pkzo::three::Camera>();
    scene.add_child(camera);

    pkzo::three::SceneRenderer renderer;

    window.on_draw([&] () {
        renderer.render(scene, *camera);
    });
    window.draw();

    auto test_image = window.save();
    ASSERT_NE(nullptr, test_image);

    // TODO image comparison with reference image.
    EXPECT_EQ(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), test_image->get_texel({0,0}));
}