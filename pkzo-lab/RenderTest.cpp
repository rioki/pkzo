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

#include "RenderTest.h"

#include <glm/gtc/matrix_transform.hpp>
#include <pkzo/opengl.h>

namespace lab
{
    RenderTest::RenderTest()
    {
        shader  = pkzo::Shader::load_file(PROJECT_DIR "assets/shaders/Textured.glsl");
        texture = pkzo::Texture::load(PROJECT_DIR "assets/textures/AngryCat.jpg");
        mesh    = pkzo::Mesh::create_plane({100.0f, 100.0f});
    }

    void RenderTest::draw(const glm::uvec2& size)
    {
        auto section = pkzo::opengl::Section{"Render Test"};

        auto hs         = glm::vec2(size) * 0.5f;
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
    }
}
