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
#include <pkzo-two/pkzo-two.h>
#include <pkzo-two-ui/pkzo-two-ui.h>
#include <pkzo-three/pkzo-three.h>
#include <glm/gtc/matrix_transform.hpp>

auto create_hello_screen(pkzo::Main& main)
{
    auto size = glm::vec2(main.get_main_window().get_size());
    auto hs = size / 2.0f;

    auto screen = std::make_shared<pkzo::two::Screen>(size);

    auto title_font        = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 50);
    auto text_font         = std::make_shared<pkzo::Font>("../assets/fonts/DejaVuSans.ttf", 22);
    auto pkzo_logo         = std::make_shared<pkzo::Texture>("../assets/textures/pkzo.png");
    auto button_background = std::make_shared<pkzo::Texture>("../assets/ui/Button_Background.png");

    auto hello = std::make_shared<pkzo::two::Text>();
    hello->set_position({0.0, pkzo_logo->get_size().y / 2.0f + 50.0f});
    hello->set_font(title_font);
    hello->set_text("Hello");
    screen->add_node(hello);

    auto logo = std::make_shared<pkzo::two::Rectangle>();
    logo->set_position({0.0, 0.0});
    logo->set_size(glm::vec2(pkzo_logo->get_size()));
    logo->set_texture(pkzo_logo);
    screen->add_node(logo);


    auto bhs = glm::vec2(button_background->get_size()) / 2.0f;
    auto exit_button = std::make_shared<pkzo::two::ui::Button>();
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
    /*pkzo::Main main;

    auto& window = main.open_window({800, 600}, pkzo::WindowMode::STATIC, "Hello Pkzo!");

    pkzo::two::ScreenRenderer screen_renderer;

    auto screen = create_hello_screen(main);

    window.on_draw([&] () {
        screen->draw(screen_renderer);
    });

    auto& mouse = main.get_mouse();
    mouse.on_button_down([&] (auto button, auto pos) {
        auto p = pkzo::two::map_to_screen(window.get_size(), screen->get_size(), pos);
        screen->handle_mouse_button_down(button, p);
    });
    mouse.on_button_up([&] (auto button, auto pos) {
        auto p = pkzo::two::map_to_screen(window.get_size(), screen->get_size(), pos);
        screen->handle_mouse_button_up(button, p);
    });

    main.run();*/

    pkzo::Main main;

    auto& window = main.open_window({800, 600}, pkzo::WindowMode::STATIC, __FUNCTION__);

    pkzo::three::Scene scene;

    auto metal_plate = std::make_shared<pkzo::three::Material>("../../data/materials/MetalPlate.jmn");
    auto metal_plate_sphere = std::make_shared<pkzo::three::Sphere>(glm::translate(glm::mat4{1.0f}, {0.0f, 1.0f, 0.0f}), 0.5f, metal_plate);
    scene.add_child(metal_plate_sphere);

    auto cobble_stone = std::make_shared<pkzo::three::Material>("../../data/materials/CobbleStone.jmn");
    auto cobble_stone_sphere = std::make_shared<pkzo::three::Sphere>(glm::translate(glm::mat4{1.0f}, {0.0f, -1.0f, 0.0f}), 0.5f, cobble_stone);
    scene.add_child(cobble_stone_sphere);

    auto light0 = std::make_shared<pkzo::three::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
    scene.add_child(light0);

    auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
    auto light1 = std::make_shared<pkzo::three::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
    scene.add_child(light1);

    auto light2 = std::make_shared<pkzo::three::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
    scene.add_child(light2);

    auto ct = glm::mat4(1.0f);
    ct = glm::translate(ct, {0.0f, 0.0f, 5.0f});
    auto camera = std::make_shared<pkzo::three::Camera>();
    camera->look_at({-5.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    camera->set_resolution(window.get_size());
    scene.add_child(camera);

    window.on_draw([&] () {
        scene.draw(*camera);
    });
    main.run();
    return 0;
}
