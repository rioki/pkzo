// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include <rex/signal.h>

using namespace std::literals::chrono_literals;

TEST(signal, void_signal_observe)
{
    rex::signal<> void_signal;

    auto count = 0u;
    void_signal.connect([&] () {
        count++;
    });

    EXPECT_EQ(0u, count);
    void_signal.emit();
    EXPECT_EQ(1u, count);
}

TEST(signal, int_signal_observe)
{
    rex::signal<int> int_signal;

    auto count = 0u;
    auto value = 0;
    int_signal.connect([&](auto v) {
        count++;
        value = v;
    });

    EXPECT_EQ(0u, count);
    int_signal.emit(42);
    EXPECT_EQ(1u, count);
    EXPECT_EQ(42, value);
}

TEST(signal, string_int_signal_observe)
{
    rex::signal<std::string, int> string_int_signal;

    auto count = 0u;
    auto value1 = std::string{};
    auto value2 = 0;
    string_int_signal.connect([&](auto v1, auto v2) {
        count++;
        value1 = v1;
        value2 = v2;
    });

    EXPECT_EQ(0u, count);
    string_int_signal.emit("Answer to the Ultimate Question of Life, the Universe, and Everything", 42);
    EXPECT_EQ(1u, count);
    EXPECT_EQ("Answer to the Ultimate Question of Life, the Universe, and Everything", value1);
    EXPECT_EQ(42, value2);
}

TEST(signal, unobserve)
{
    rex::signal<> void_signal;

    auto count = 0u;
    auto c = void_signal.connect([&]() {
        count++;
    });

    void_signal.disconnect(c);

    EXPECT_EQ(0u, count);
    void_signal.emit();
    EXPECT_EQ(0u, count);
}

TEST(signal, obverver_count)
{
    rex::signal<> void_signal;

    auto c = void_signal.emit();
    EXPECT_EQ(0u, c);

    auto c1 = void_signal.connect([] () {});
    auto c2 = void_signal.connect([]() {});

    c = void_signal.emit();
    EXPECT_EQ(2u, c);

    void_signal.disconnect(c2);

    c = void_signal.emit();
    EXPECT_EQ(1u, c);
}

void process_item(int) {}

TEST(signal, getting_started)
{
    std::stringstream cout;
    std::vector<int> items(4);

    rex::signal<unsigned int, unsigned int> processing_signal;

    processing_signal.connect([&] (auto done, auto total) {
        auto percent = static_cast<float>(done) / static_cast<float>(total) * 100.0f;
        cout << "Handled " << done << " of " << total << " [" << percent << "%]" << std::endl;
    });

    for (auto i = 0u; i < items.size(); i++)
    {
        process_item(items[i]);
        processing_signal.emit(i+1, static_cast<unsigned int>(items.size()));
    }

    auto ref = "Handled 1 of 4 [25%]\n"
               "Handled 2 of 4 [50%]\n"
               "Handled 3 of 4 [75%]\n"
               "Handled 4 of 4 [100%]\n";
    EXPECT_EQ(ref, cout.str());
}

class Mouse
{
public:

    rex::signal<int, int>& get_move_signal()
    {
        return move_signal;
    }

    void update()
    {
        auto x = std::rand();
        auto y = std::rand();

        move_signal.emit(x % 2 ? -1 : 1, y % 2 ? -1 : 1);
    }

private:
    rex::signal<int, int> move_signal;
};

class PlayerController
{
public:
    void activate(Mouse& mouse)
    {
        move_con = mouse.get_move_signal().connect([this] (auto x, auto y) {
            control(x, y);
        });
    }

    void deactivate(Mouse& mouse)
    {
        mouse.get_move_signal().disconnect(move_con);
    }

    void control(int x, int y)
    {
        u = x;
        v = y;
    }

    std::tuple<int, int> get_uv() const
    {
        return std::make_tuple(u, v);
    }

private:
    int u = 0;
    int v = 0;
    rex::connection move_con;
};

TEST(signal, life_time)
{
    std::atomic<bool> running = true;
    Mouse mouse;

    auto f = std::async(std::launch::async, [&] () {
        while (running)
        {
            mouse.update();
        }
    });

    {
        PlayerController ctrl;
        ctrl.activate(mouse);
        std::this_thread::sleep_for(10ms);
        auto [u, v] = ctrl.get_uv();
        EXPECT_NE(0, u);
        EXPECT_NE(0, v);
        ctrl.deactivate(mouse);
    }
    // ctrl is out of scope, so it can crash here, if the deregistration does not work well
    std::this_thread::sleep_for(5ms);

    running = false;
    f.get();
}

TEST(signal, implicit_interface)
{
    auto on_something = rex::signal<int>{};

    auto count = 0u;
    auto value = 0;
    on_something([&](auto v) {
        count++;
        value = v;
    });

    EXPECT_EQ(0u, count);

    on_something(42);

    EXPECT_EQ(1u, count);
    EXPECT_EQ(42, value);
}
