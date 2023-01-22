// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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

#include "pch.h"

TEST(Screen, init)
{
    auto screen = pkzo::Screen(glm::vec2(640.0f, 480.0f));
    EXPECT_GLM_NEAR(glm::mat3(1.0), screen.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(640.0f, 480.0f), screen.get_size(), 1e-4f);
}

TEST(Screen, in_engine_has_engine)
{
    auto engine = pkzo::Engine();

    auto screen = std::make_shared<pkzo::Screen>();
    engine.set_overlay(screen);

    engine.on_tick([&] () {
        EXPECT_EQ(&engine, screen->get_engine());
    });

    engine.run(1u);
}

TEST(Screen, GRAPHICAL_render_plain_rectangle)
{
    auto engine = pkzo::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto screen = std::make_shared<pkzo::Screen>(glm::vec2(800.0f, 600.0f));

    auto rt = glm::mat3(1.0f);
    rt = glm::translate(rt, {-25.0f, 50.0f});
    rt = glm::rotate(rt, glm::radians(35.0f));
    auto rectangle = pkzo::Rectangle(rt, {250.0f, 200.0f}, {1.0f, 0.7f, 0.5f, 1.0f});
    screen->add_node(rectangle);

    engine.set_overlay(screen);

    engine.run(3u);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(Screen, GRAPHICAL_render_textured_rectangle)
{
    auto engine = pkzo::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto screen = std::make_shared<pkzo::Screen>(glm::vec2(800.0f, 600.0f));

    auto rt = glm::mat3(1.0f);
    rt = glm::translate(rt, {25.0f, -50.0f});
    rt = glm::rotate(rt, glm::radians(-35.0f));
    auto rectangle = pkzo::Rectangle(rt, {200.0f, 250.0f}, {1.0f, 0.7f, 0.5f, 1.0f}, std::make_shared<pkzo::Texture>(pkzo::test::get_test_input() / "AngryCat.jpg"));
    screen->add_node(rectangle);

    engine.set_overlay(screen);

    engine.run(3u);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(Screen, GRAPHICAL_render_text)
{
    auto engine = pkzo::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       pkzo::WindowMode::STATIC);

    engine.start_system<pkzo::SdlGraphicSystem>();

    auto screen = std::make_shared<pkzo::Screen>(glm::vec2(800.0f, 600.0f));

    auto font = std::make_shared<pkzo::Font>(pkzo::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 32);
    auto text = std::make_shared<pkzo::Text>(glm::mat3(1.0f), "Ice Engine", font, glm::vec4(1.0f));
    screen->add_node(text);

    engine.set_overlay(screen);

    engine.run(3u);

    const auto* gs = engine.get_system<pkzo::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(Screen, forward_to_hitarea)
{
    auto engine = pkzo::Engine{}; // only for activation
    auto screen = pkzo::Screen(glm::vec2(640.0f, 480.0f));

    auto hitarea = pkzo::HitArea(glm::mat3(1.0f), glm::vec2(150.0f, 50.0f));

    auto mouse_down_count  = 0u;
    auto mouse_down_inside = false;
    auto mouse_down_button = pkzo::MouseButton::NONE;
    auto mouse_down_pos    = glm::vec2(0.0f);
    hitarea.on_mouse_down([&] (auto inside, auto button, auto pos) {
        mouse_down_count++;
        mouse_down_inside = inside;
        mouse_down_button = button;
        mouse_down_pos    = pos;
    });
    auto mouse_up_count  = 0u;
    auto mouse_up_inside = false;
    auto mouse_up_button = pkzo::MouseButton::NONE;
    auto mouse_up_pos    = glm::vec2(0.0f);
    hitarea.on_mouse_up([&] (auto inside, auto button, auto pos) {
        mouse_up_count++;
        mouse_up_inside = inside;
        mouse_up_button = button;
        mouse_up_pos    = pos;
    });

    auto click_count  = 0u;
    hitarea.on_click([&] () {
        click_count++;
    });
    auto right_click_count  = 0u;
    hitarea.on_right_click([&] () {
        right_click_count++;
    });

    screen.add_node(hitarea);

    screen.set_engine(&engine);

    auto pos1 = glm::vec2(12.0f, 14.0f);
    screen.handle_mouse_down(pkzo::MouseButton::LEFT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(12.0f, 14.0f), 1e-4f);

    auto pos2 = glm::vec2(16.0f, 18.0f);
    screen.handle_mouse_up(pkzo::MouseButton::LEFT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(1u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(16.0f, 18.0f), 1e-4f);

    screen.set_engine(nullptr);
}

