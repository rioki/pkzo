// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <limits>

#include <ice/Engine.h>
#include <ice/System.h>

#include "test_utils.h"

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