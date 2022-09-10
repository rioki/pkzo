// Ice Engine
// Copyright 2022 Sean Farrell
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

#include <ice/ice.h>

#include "test_env.h"
#include "texture_checks.h"

TEST(ConsoleSystem, start_system)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::ConsoleSystem>();

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);
}

TEST(ConsoleSystem, handles_empty_line)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::ConsoleSystem>();

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);

    console->exec("");
}

TEST(ConsoleSystem, register_and_execute_line)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::ConsoleSystem>();

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);

    std::vector<std::string> buffer;
    console->define("echo", [&buffer] (const auto& args) mutable {
        auto line = ice::join({begin(args) + 1, end(args)}, " ");
        buffer.push_back(line);
    });

    console->exec("echo one");
    ASSERT_EQ(1u, buffer.size());
    EXPECT_EQ("one", buffer[0]);

    console->exec("echo 1 2 3");
    ASSERT_EQ(2u, buffer.size());
    EXPECT_EQ("1 2 3", buffer[1]);

    console->exec("echo 1  2 3");
    ASSERT_EQ(3u, buffer.size());
    EXPECT_EQ("1 2 3", buffer[2]);

    console->exec("echo \"Hello  World!\"");
    ASSERT_EQ(4u, buffer.size());
    EXPECT_EQ("Hello  World!", buffer[3]);
}

class CatScreen : public ice::Screen
{
public:
    CatScreen(ice::Engine& engine, const glm::vec2& size)
    : Screen(size)
    {
        auto angry_cat = engine.load_asset<ice::Texture>("AngryCat.jpg");
        auto rectangle = std::make_shared<ice::Rectangle>(glm::mat3(1.0f), size, angry_cat);
        add_node(rectangle);
    }
};


TEST(ConsoleSystem, GRAPHICAL_render_hidden_console)
{
    auto engine = ice::Engine{};

    engine.add_asset_folder(ice::test::get_test_input());
    engine.add_asset_folder(ice::test::get_asset_folder());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);
    settings.set_value("ConsoleSystem", "font",       "fonts/DejaVuSansMono.ttf");

    engine.start_system<ice::GraphicSystem>();
    engine.start_system<ice::InputSystem>();
    engine.start_system<ice::ConsoleSystem>();

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);
;
    console->write("Hello World!");

    engine.set_overlay(std::make_shared<CatScreen>(engine, glm::vec2(800, 600)));

    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(ConsoleSystem, GRAPHICAL_render_console_log)
{
    auto engine = ice::Engine{};

    engine.add_asset_folder(ice::test::get_test_input());
    engine.add_asset_folder(ice::test::get_asset_folder());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);
    settings.set_value("ConsoleSystem", "font",       "fonts/DejaVuSansMono.ttf");
    settings.set_value("ConsoleSystem", "lines",      5);

    engine.start_system<ice::GraphicSystem>();
    engine.start_system<ice::InputSystem>();
    engine.start_system<ice::ConsoleSystem>();

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);

    console->write("Line 1");
    console->write("Line 2");
    console->write("Line 3");
    console->write("Long Line 4, with some extra stuff.");
    console->write("Line 5");
    console->write("Line 6");

    console->show();

    engine.set_overlay(std::make_shared<CatScreen>(engine, glm::vec2(800, 600)));

    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}

TEST(ConsoleSystem, GRAPHICAL_show_on_console_key)
{
    auto engine = ice::Engine{};

    engine.add_asset_folder(ice::test::get_test_input());
    engine.add_asset_folder(ice::test::get_asset_folder());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution",  glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",        ice::WindowMode::STATIC);
    settings.set_value("ConsoleSystem", "font",        "fonts/DejaVuSansMono.ttf");
    settings.set_value("ConsoleSystem", "consoel_key", ice::Key::F1);
    settings.set_value("ConsoleSystem", "lines",       5);

    engine.start_system<ice::GraphicSystem>();
    engine.start_system<ice::InputSystem>();
    engine.start_system<ice::ConsoleSystem>();

    auto input = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto console = engine.get_system<ice::ConsoleSystem>();
    ASSERT_NE(nullptr, console);

    EXPECT_FALSE(console->is_visible());

    input->inject_key_down(ice::KeyMod::NONE, ice::Key::F1);
    engine.tick();
    input->inject_key_up(ice::KeyMod::NONE, ice::Key::F1);
    engine.tick();

    EXPECT_TRUE(console->is_visible());

    input->inject_key_down(ice::KeyMod::NONE, ice::Key::F1);
    engine.tick();
    input->inject_key_up(ice::KeyMod::NONE, ice::Key::F1);
    engine.tick();

    EXPECT_FALSE(console->is_visible());
}

TEST(ConsoleSystem, GRAPHICAL_render_console_input)
{
    auto engine = ice::Engine{};

    engine.add_asset_folder(ice::test::get_test_input());
    engine.add_asset_folder(ice::test::get_asset_folder());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);
    settings.set_value("ConsoleSystem", "font",       "fonts/DejaVuSansMono.ttf");
    settings.set_value("ConsoleSystem", "lines",      5);

    engine.start_system<ice::GraphicSystem>();
    engine.start_system<ice::InputSystem>();
    engine.start_system<ice::ConsoleSystem>();

    auto input = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto console = engine.get_system<ice::ConsoleSystem>();
    EXPECT_NE(nullptr, console);

    console->show();

    engine.set_overlay(std::make_shared<CatScreen>(engine, glm::vec2(800, 600)));

    auto line = std::string("echo Hello World!");
    for (const auto& c : line)
    {
        input->inject_text(std::string(1, c));
    }

    engine.tick();
    engine.tick();
    engine.tick();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    auto screenshot = gs->get_screenshot();
    EXPECT_TEXTURE_REF_EQ(screenshot);
}
