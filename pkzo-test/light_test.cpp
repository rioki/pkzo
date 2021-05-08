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

TEST(AmbientLight, default_construct)
{
    auto light = pkzo::AmbientLight{};
    EXPECT_GLM_NEAR(glm::mat4(1.0f), light.get_transform(), 1e-6f);
    EXPECT_GLM_NEAR(glm::vec3(0.1f), light.get_color(), 1e-6f);
}

TEST(AmbientLight, initilize)
{
    auto light = pkzo::AmbientLight{{0.106f, 0.161f, 0.2f}};
    EXPECT_GLM_NEAR(glm::mat4(1.0f), light.get_transform(), 1e-6f);
    EXPECT_GLM_NEAR(glm::vec3(0.106f, 0.161f, 0.2f), light.get_color(), 1e-6f);
}

TEST(DirectionalLight, default_construct)
{
    auto light = pkzo::DirectionalLight{};
    EXPECT_GLM_NEAR(glm::mat4(1.0f), light.get_transform(), 1e-6f);
    EXPECT_GLM_NEAR(glm::vec3(1.0f), light.get_color(), 1e-6f);
}

TEST(DirectionalLight, initilize)
{
    auto t = glm::inverse(glm::lookAt(glm::vec3(0.0f), {1.0f, 2.0f, 3.0f}, {0.0f, 1.0f, 0.0f}));
    auto light = pkzo::DirectionalLight{t, {0.839f, 0.718f, 0.573f}};
    EXPECT_GLM_NEAR(t, light.get_transform(), 1e-6f);
    EXPECT_GLM_NEAR(glm::vec3(0.839f, 0.718f, 0.573f), light.get_color(), 1e-6f);
}
