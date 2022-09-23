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

using namespace std::chrono_literals;
using fsec = std::chrono::duration<float>;

TEST(StatsSystem, start_system)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);
}

TEST(StatsSystem, time_based_stat)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::TIME, "tps");

    auto start = std::chrono::steady_clock::now();
    auto count = 0u;
    engine.on_tick([&] ()
    {
        // slow down
        std::this_thread::sleep_for(100ms);

        stats->increment("tps");
        count++;

        auto now = std::chrono::steady_clock::now();
        if (now - start > 2s)
        {
            engine.stop();
        }
    });
    engine.run();

    auto end = std::chrono::steady_clock::now();
    auto dt  = fsec(end - start).count();
    auto tps = static_cast<float>(count) / dt;

    // not super accurate, there is start up and tear down in that check
    EXPECT_NEAR(tps, stats->get("tps"), 0.5f);
}

TEST(StatsSystem, time_based_stat_2)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::TIME, "tps");

    auto start = std::chrono::steady_clock::now();
    auto count = 0u;
    engine.on_tick([&] ()
    {
        // slow down
        std::this_thread::sleep_for(100ms);

        stats->increment("tps", 2.0f);
        count++;

        auto now = std::chrono::steady_clock::now();
        if (now - start > 2s)
        {
            engine.stop();
        }
    });
    engine.run();

    auto end = std::chrono::steady_clock::now();
    auto dt  = fsec(end - start).count();
    auto tps = (static_cast<float>(count) * 2.0f) / dt;

    // not super accurate, there is start up and tear down in that check
    EXPECT_NEAR(tps, stats->get("tps"), 0.5f);
}

TEST(StatsSystem, frame_based_stat)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::FRAME, "micro_ticks");

    auto count = 0u;
    engine.on_tick([&] ()
    {
        // slow down
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks");
        count++;

        if (count >= 5)
        {
            engine.stop();
        }
    });
    engine.run();

    EXPECT_NEAR(5.0f, stats->get("micro_ticks"), 0.1f);
}

TEST(StatsSystem, frame_based_stat_2)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::FRAME, "micro_ticks");

    auto count = 0u;
    engine.on_tick([&] ()
    {
        // slow down
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks", 1.0f);
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks", 2.0f);
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks", 3.0f);
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks", 4.0f);
        std::this_thread::sleep_for(20ms);
        stats->increment("micro_ticks", 5.0f);
        count++;

        if (count >= 5)
        {
            engine.stop();
        }
    });
    engine.run();

    EXPECT_NEAR(15.0f, stats->get("micro_ticks"), 0.1f);
}

TEST(StatsSystem, value_based_stat)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::VALUE, "count");

    auto count = 0u;
    engine.on_tick([&] ()
    {
        // slow down
        std::this_thread::sleep_for(20ms);
        stats->set("count", static_cast<float>(count));
        count++;

        if (count >= 5)
        {
            engine.stop();
        }
    });
    engine.run();

    EXPECT_NEAR(4.0f, stats->get("count"), 0.1f);
}

namespace
{
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
}

TEST(StatsSystem, GRAPHICAL_render_stats)
{
    auto engine = ice::Engine{};

    engine.add_asset_folder(ice::test::get_test_input());
    engine.add_asset_folder(ice::test::get_asset_folder());

    auto& settings = engine.get_settings();
    settings.set_value("GraphicSystem", "resolution", glm::uvec2(800, 600));
    settings.set_value("GraphicSystem", "mode",       ice::WindowMode::STATIC);
    settings.set_value("ConsoleSystem", "font",       "fonts/DejaVuSansMono.ttf");
    settings.set_value("ConsoleSystem", "lines",      5);

    engine.start_system<ice::SdlGraphicSystem>();
    engine.start_system<ice::SdlInputSystem>();
    engine.start_system<ice::StatsSystem>();

    auto stats = engine.get_system<ice::StatsSystem>();
    EXPECT_NE(nullptr, stats);

    stats->define(ice::StatType::FRAME, "ticks");
    stats->define(ice::StatType::VALUE, "count");

    stats->show();

    engine.set_overlay(std::make_shared<CatScreen>(engine, glm::vec2(800, 600)));

    auto start = std::chrono::steady_clock::now();
    auto count = 0u;
    engine.on_tick([&] ()
    {
        std::this_thread::sleep_for(20ms);
        stats->increment("ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("ticks");
        std::this_thread::sleep_for(20ms);
        stats->increment("ticks");

        stats->set("count", static_cast<float>(count));
        count++;

        auto now = std::chrono::steady_clock::now();
        if (now - start > 3s)
        {
            engine.stop();
        }
    });
    engine.run();

    const auto* gs = engine.get_system<ice::GraphicSystem>();
    ASSERT_NE(nullptr, gs);
    EXPECT_TEXTURE_REF_EQ(gs->get_screenshot());
}
