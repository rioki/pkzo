// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include <pkzo/Texture.h>
#include <pkzo/Mesh.h>
#include <pkzo/Shader.h>

#include <pkzo/Window.h>

#include <glm/gtc/matrix_transform.hpp>

#include "glm_gtest.h"
#include "pkzo_test.h"

TEST(OpenGL, GRAPH_render_textured_quad)
{
    auto window = pkzo::Window{{800,600}, "Test"};

    auto texture = pkzo::Texture::load(pkzo::test::get_test_input() / "AngryCat.jpg");
    auto shader  = pkzo::Shader::load_file(pkzo::test::get_test_input() / "shaders/textured.glsl");
    auto mesh    = pkzo::Mesh::create_plane({250.0f, 250.0f});

    window.get_draw_signal().connect([&] () {
        auto hs = glm::vec2(window.get_drawable_size()) * 0.5f;
        auto projection = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);
        auto view       = glm::mat4(1.0f);
        auto model      = glm::mat4(1.0f);

        shader->bind();
        shader->set_uniform("pkzo_ProjectionMatrix", projection);
        shader->set_uniform("pkzo_ViewMatrix",       view);
        shader->set_uniform("pkzo_ModelMatrix",      model);

        texture->bind(0u);
        shader->set_uniform("test_Texture", 0u);
        shader->set_uniform("test_Color",   glm::vec3{1.0f, 1.0f, 1.0f});

        mesh->draw();
    });

    window.draw();
    window.draw();

    auto screenshot = window.save_screen();
    EXPECT_GLM_EQ(glm::uvec2(800, 600), screenshot->get_size());
    EXPECT_TEXTURE_REF_EQ(screenshot);
}
