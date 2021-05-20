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

#include <pkzo/Text.h>
#include <pkzo/Font.h>
#include <pkzo/Material.h>
TEST(Text, create)
{
    auto font = std::make_shared<pkzo::Font>("../../data/fonts/DejaVuSans.ttf", 32);
    auto text = pkzo::Text("pkzo", font, std::make_shared<pkzo::Material>());
    //EXPECT_GLM_EQ(glm::vec2(0.0f), text.get_position());
    EXPECT_GLM_EQ(glm::vec2(font->estimate("pkzo")), text.get_size());
    EXPECT_EQ(font, text.get_font());
    EXPECT_EQ("pkzo", text.get_text());
}

TEST(Text, render)
{
    pkzo::Window window({800, 600}, pkzo::WindowMode::STATIC, __FUNCTION__);

    pkzo::Screen screen(glm::vec2(window.get_size()));
    auto font = std::make_shared<pkzo::Font>("../../data/fonts/DejaVuSans.ttf", 32);
    auto text = std::make_shared<pkzo::Text>("pkzo", font, pkzo::make_emissive_material(glm::vec3(1.0f)));
    screen.add_node(text);

    window.on_draw([&] () {
        screen.draw();
    });
    window.draw();
    window.draw();

    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/reference/Text-render-ref.png"), *window.save());
}