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

#include <gtest/gtest.h>
#include <pkzo/pkzo.h>

#include "glm_gtest.h"
#include "pkzo_gtest.h"

TEST(window, create)
{
    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    EXPECT_EQ(window.get_title(), "test");
    EXPECT_GLM_EQ(window.get_size(), glm::uvec2(800u, 600u));
    EXPECT_EQ(window.get_state(), pkzo::WindowState::WINDOW);
    EXPECT_EQ(window.get_api(), pkzo::Api::OPENGL);

    window.draw();
}

TEST(window, screenshot)
{
    auto window = pkzo::Window({
        .title = "test",
        .size  = glm::uvec2(800u, 600u),
        .state = pkzo::WindowState::WINDOW,
        .api   = pkzo::Api::OPENGL
    });

    window.draw();
    window.draw();

    EXPECT_TEXTURE_REF_EQ(window.screenshot());
}
