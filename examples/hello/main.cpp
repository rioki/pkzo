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

#include <pkzo/pkzo.h>
#include <glm/gtc/matrix_transform.hpp>

auto create_hello_screen(pkzo::Engine& main)
{
    auto size = glm::vec2(main.get_main_window().get_size());
    auto hs = size / 2.0f;

    auto screen = std::make_shared<pkzo::Screen>(size);

    auto font      = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 50);
    auto pkzo_logo = std::make_shared<pkzo::Texture>("../assets/textures/pkzo.png");

    auto white_emissive_material = pkzo::make_emissive_material(glm::vec3(1.0f));
    auto hello_pos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, pkzo_logo->get_size().y / 2.0f + 50.0f, 0.0f));
    auto hello = std::make_shared<pkzo::Text>(hello_pos, "Hello", font, white_emissive_material);
    screen->add_node(hello);

    auto logo_pos = glm::mat4(1.0f);
    auto white_logo_material = pkzo::make_emissive_material(pkzo_logo);
    auto logo = std::make_shared<pkzo::Rectangle>(logo_pos, glm::vec2(pkzo_logo->get_size()), white_logo_material);
    screen->add_node(logo);

    return screen;
}

int main(int argc, char* argv[])
{
    pkzo::Engine main("pkzo-hello");

    auto& window = main.get_main_window();
    window.set_caption("Hello Pkzo!");

    auto screen = create_hello_screen(main);
    window.on_draw([&] () {
        screen->draw();
    });

    main.run();
    return 0;
}
