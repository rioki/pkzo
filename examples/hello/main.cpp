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
#include <pkzo2d/pkzo2d.h>
#include <pkzoui/pkzoui.h>

auto create_hello_screen(pkzo::Main& main)
{
    auto size = glm::vec2(main.get_main_window().get_size());
    auto hs = size / 2.0f;

    auto screen = std::make_shared<pkzo2d::Screen>(size);

    auto title_font        = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 50);
    auto text_font         = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 22);
    auto pkzo_logo         = std::make_shared<pkzo::Texture>("../assets/textures/pkzo.png");
    auto button_background = std::make_shared<pkzo::Texture>("../assets/ui/Button_Background.png");

    auto hello = std::make_shared<pkzo2d::Text>();
    hello->set_position({0.0, pkzo_logo->get_size().y / 2.0f + 50.0f});
    hello->set_font(title_font);
    hello->set_text("Hello");
    screen->add_node(hello);

    auto logo = std::make_shared<pkzo2d::Rectangle>();
    logo->set_position({0.0, 0.0});
    logo->set_size(glm::vec2(pkzo_logo->get_size()));
    logo->set_texture(pkzo_logo);
    screen->add_node(logo);


    auto bhs = glm::vec2(button_background->get_size()) / 2.0f;
    auto exit_button = std::make_shared<pkzoui::Button>();
    exit_button->set_position({hs.x - bhs.x - 10.0f, -hs.y + bhs.y + 10.0f});
    exit_button->set_caption("Close");
    exit_button->set_caption_color({0.9f, 0.9f, 0.9f, 1.0f});
    exit_button->set_caption_font(text_font);
    exit_button->set_background(button_background);
    exit_button->on_click([&] () {
        main.stop();
    });
    screen->add_node(exit_button);

    return screen;
}

int main(int argc, char* argv[])
{
    pkzo::Main main;

    auto& window = main.open_window({800, 600}, pkzo::WindowMode::STATIC, "Hello Pkzo!");

    pkzo2d::ScreenRenderer screen_renderer;

    auto screen = create_hello_screen(main);

    window.on_draw([&] () {
        screen->draw(screen_renderer);
    });

    auto& mouse = main.get_mouse();
    mouse.on_button_down([&] (auto button, auto pos) {
        auto p = pkzo2d::map_to_screen(window.get_size(), screen->get_size(), pos);
        screen->handle_mouse_button_down(button, p);
    });
    mouse.on_button_up([&] (auto button, auto pos) {
        auto p = pkzo2d::map_to_screen(window.get_size(), screen->get_size(), pos);
        screen->handle_mouse_button_up(button, p);
    });

    main.run();
    return 0;
}
