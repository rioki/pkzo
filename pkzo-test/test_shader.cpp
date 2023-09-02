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

TEST(Shader, load_without_OpenGL)
{
    auto shader  = pkzo::Shader::load_file(pkzo::test::get_test_input() / "shaders/empty.glsl");
    // and now?
}

TEST(Shader, throw_invalid_file)
{
    EXPECT_THROW(pkzo::Shader::load_file(pkzo::test::get_test_input() / "UT6_Ubershader.glsl"), std::runtime_error);
}

TEST(Shader, GRAPH_compile_empty)
{
    auto window = pkzo::Window{{800,600}, "Test"};

    auto shader  = pkzo::Shader::load_file(pkzo::test::get_test_input() / "shaders/empty.glsl");

    std::stringstream buffer;
    shader->compile(buffer);

    EXPECT_EQ("", buffer.str());
}

TEST(Shader, GRAPH_compile_simple)
{
    auto window = pkzo::Window{{800,600}, "Test"};

    auto shader  = pkzo::Shader::load_file(pkzo::test::get_test_input() / "shaders/textured.glsl");

    std::stringstream buffer;
    try
    {
        shader->compile(buffer);
    }
    catch (...)
    {
        EXPECT_EQ("", buffer.str());
        throw;
    }

    EXPECT_EQ("", buffer.str());
}
