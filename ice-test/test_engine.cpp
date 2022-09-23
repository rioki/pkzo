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

#include <limits>

#include <ice/ice.h>

class CountSystem : public ice::System
{
public:
    CountSystem(ice::Engine& e) noexcept
    : System(e) {}

    void tick() override
    {
        count++;
    }

    unsigned int get_count() const noexcept
    {
        return count;
    }

private:
    unsigned int count = 0u;
};

class StopSystem : public ice::System
{
public:
    StopSystem(ice::Engine& e) noexcept
    : System(e)
    {
        const auto& settings = engine.get_settings();
        stop_count = settings.get_value("StopSystem", "stop_count", stop_count);
    }

    void tick() override
    {
        assert(count < stop_count);
        count++;
        if (count == stop_count)
        {
            engine.stop();
        }
    }

    unsigned int get_count() const noexcept
    {
        return count;
    }

private:
    unsigned int count      = 0u;
    unsigned int stop_count = std::numeric_limits<unsigned int>::max();
};

class ActivatableSystem : public ice::System
{
public:
    ActivatableSystem(ice::Engine& e) noexcept
    : System(e) {}

    void activate()
    {
        EXPECT_FALSE(active);
        active = true;
        count++;
    }

    void deactivate()
    {
        EXPECT_TRUE(active);
        active = false;
        count++;
    }

    bool is_active() const noexcept
    {
        return active;
    }

    unsigned int get_count() const noexcept
    {
        return count;
    }

private:
    bool         active = false;
    unsigned int count  = 0u;
};

TEST(Engine, load_settings)
{
    auto engine = ice::Engine{};

    const auto& a = engine.get_settings();
    EXPECT_EQ("fallback", a.get_value("test", "greeting", "fallback"));

    engine.load_settings(ice::test::get_test_input() / "TestSettings.json");

    const auto& b = engine.get_settings();
    EXPECT_EQ("Hello World!", b.get_value("test", "greeting", "fallback"));
}

TEST(Engine, start_system)
{
    auto engine = ice::Engine{};

    engine.start_system<CountSystem>();

    const auto* count = engine.get_system<CountSystem>();
    ASSERT_NE(nullptr, count);
    EXPECT_EQ(0u, count->get_count());

    engine.tick();

    EXPECT_EQ(1u, count->get_count());
}

TEST(Engine, stops)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("StopSystem", "stop_count", 5u);

    engine.start_system<CountSystem>();
    engine.start_system<StopSystem>();

    engine.run();

    const auto* count = engine.get_system<CountSystem>();
    ASSERT_NE(nullptr, count);
    EXPECT_EQ(5u, count->get_count());
}

TEST(Engine, tick_signal)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("StopSystem", "stop_count", 5u);

    engine.start_system<StopSystem>();

    auto count = 0u;
    engine.on_tick([&] () {
        count++;
    });

    engine.run();

    EXPECT_EQ(5u, count);
}

TEST(Engine, devices)
{
    auto engine = ice::Engine{};

    auto w0 = engine.get_window();
    EXPECT_EQ(nullptr, w0);
    auto m0 = engine.get_mouse();
    EXPECT_EQ(nullptr, m0);
    auto k0 = engine.get_keyboard();
    EXPECT_EQ(nullptr, k0);
    auto j0 = engine.get_joysticks();
    EXPECT_TRUE(j0.empty());

    engine.start_system<ice::SdlGraphicSystem>();
    engine.start_system<ice::SdlInputSystem>();

    auto window = engine.get_window();
    EXPECT_NE(nullptr, window);

    const auto* mouse = engine.get_mouse();
    EXPECT_NE(nullptr, mouse);

    const auto* keyboard = engine.get_keyboard();
    EXPECT_NE(nullptr, keyboard);

    auto js = engine.get_joysticks();
    // if there are some, check if they are valid
    for (const auto& j : js)
    {
        EXPECT_NE(nullptr, j);
    }
}

TEST(Engine, overlay_change_sync_on_tick)
{
    auto engine = ice::Engine{};

    engine.activate();

    EXPECT_EQ(nullptr, engine.get_overlay());

    auto screen = std::make_shared<ice::Screen>(glm::vec2(800, 600));
    engine.set_overlay(screen);
    EXPECT_EQ(nullptr, engine.get_overlay());

    engine.tick();
    EXPECT_EQ(screen, engine.get_overlay());

    engine.deactivate();
}

TEST(Engine, activate_systems)
{
    auto engine = ice::Engine{};

    auto& settings = engine.get_settings();
    settings.set_value("StopSystem", "stop_count", 5u);

    engine.start_system<ActivatableSystem>();
    engine.start_system<StopSystem>();

    auto activatable = engine.get_system<ActivatableSystem>();
    EXPECT_FALSE(activatable->is_active());

    engine.on_tick([&] () {
        EXPECT_TRUE(activatable->is_active());
    });

    engine.run();

    EXPECT_FALSE(activatable->is_active());
    EXPECT_EQ(2u, activatable->get_count());
}


