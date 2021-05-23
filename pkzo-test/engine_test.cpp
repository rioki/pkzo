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

TEST(Main, contruct)
{
    pkzo::Main Main("pkzo-test");
    EXPECT_EQ("pkzo-test", Main.get_id());
}

TEST(Main, environment)
{
    pkzo::Main Main("pkzo-test");

    auto user_folder = Main.get_user_folder();
    EXPECT_EQ("pkzo-test", user_folder.filename());

    auto temp_folder = Main.get_temp_folder();
    EXPECT_EQ("pkzo-test", user_folder.filename());
    EXPECT_NE(user_folder, temp_folder);
}

TEST(Engine, arguments)
{
    int   argc = 2;
    const char* argv[2] = {"pkzo-test", "arguments"};
    pkzo::Engine engine("pkzo-test", argc, argv);
    EXPECT_EQ("pkzo-test", engine.get_id());
}

TEST(Engine, settings)
{
    pkzo::Settings ref;
    ref.set_value("Graphic", "fullscreen", false);
    ref.set_value("Graphic", "resolution", glm::uvec2(1600, 900));
    ref.save(pkzo::test::get_user_folder() / "pkzo-test" / "settings.json");

    pkzo::Main Main(pkzo::test::ENGINE_ID);
    auto& settings = Main.get_settings();
    EXPECT_EQ(false, settings.get_value("Graphic", "fullscreen", false));
    EXPECT_EQ(glm::uvec2(1600, 900), settings.get_value("Graphic", "resolution", glm::uvec2(800, 600)));
}

TEST(Main, open_window)
{
    pkzo::test::setup_test_settings({1600, 900});

    pkzo::Main Main(pkzo::test::ENGINE_ID);
    auto& window = Main.get_main_window();
    EXPECT_EQ(pkzo::WindowMode::STATIC, window.get_mode());
    EXPECT_EQ(glm::uvec2(1600, 900), window.get_size());
}

TEST(Main, dont_init_anything)
{
    pkzo::test::setup_test_settings({1600, 900});

    pkzo::Main Main(pkzo::test::ENGINE_ID, pkzo::EngineInit::NONE);

    auto& settings = Main.get_settings();
    EXPECT_FALSE(settings.has_value("Graphic", "resolution"));
    EXPECT_EQ(0u, Main.get_open_windows());
}

TEST(Engine, on_handlers_can_disconnect)
{
    pkzo::test::setup_test_settings();

    pkzo::Engine engine(pkzo::test::ENGINE_ID, pkzo::EngineInit::NONE);

    auto tick_con = engine.on_tick([] (auto dt) {});
    EXPECT_NO_THROW(engine.get_tick_signal().disconnect(tick_con));

    auto quit_con = engine.on_quit([] () {});
    EXPECT_NO_THROW(engine.get_quit_signal().disconnect(quit_con));
}