// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

TEST(InputSystem, has_devices_after_load)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::InputSystem>();

    const auto* is = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, is);

    const auto* mouse = is->get_mouse();
    ASSERT_NE(nullptr, mouse);

    const auto* keyboard = is->get_keyboard();
    ASSERT_NE(nullptr, keyboard);

    auto js = is->get_joysticks();
    // if there are some, check if they are valid
    for (const auto& j : js)
    {
        ASSERT_NE(nullptr, j);
    }
}

TEST(InputSystem, inject_mouse_events)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::InputSystem>();

    auto* input = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto* mouse = input->get_mouse();
    ASSERT_NE(nullptr, mouse);

    auto last_button       = ice::MouseButton::NONE;
    auto last_position     = glm::ivec2(0);
    auto last_move         = glm::ivec2(0);
    auto button_down_count = 0u;
    auto button_up_count   = 0u;
    auto move_count        = 0u;
    auto wheel_count       = 0u;
    mouse->on_button_down([&] (auto button, auto pos) {
        last_button   = button;
        last_position = pos;
        button_down_count++;
    });
    mouse->on_button_up([&] (auto button, auto pos) {
        last_button   = button;
        last_position = pos;
        button_up_count++;
    });
    mouse->on_move([&] (auto pos, auto mov) {
        last_position = pos;
        last_move     = mov;
        move_count++;
    });
    mouse->on_wheel([&] (auto mov) {
        last_move     = mov;
        wheel_count++;
    });

    input->inject_mouse_button_down(ice::MouseButton::LEFT, glm::ivec2(1, 2));
    engine.tick();

    EXPECT_EQ(last_button,       ice::MouseButton::LEFT);
    EXPECT_EQ(last_position,     glm::ivec2(1, 2));
    EXPECT_EQ(last_move,         glm::ivec2(0));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   0u);
    EXPECT_EQ(move_count,        0u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_button_up(ice::MouseButton::RIGHT, glm::ivec2(3, 4));
    engine.tick();

    EXPECT_EQ(last_button,       ice::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(3, 4));
    EXPECT_EQ(last_move,         glm::ivec2(0));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        0u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_move(glm::ivec2(5, 6), glm::ivec2(7, 8));
    engine.tick();

    EXPECT_EQ(last_button,       ice::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(5, 6));
    EXPECT_EQ(last_move,         glm::ivec2(7, 8));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        1u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_wheel(glm::ivec2(9, 10));
    engine.tick();

    EXPECT_EQ(last_button,       ice::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(5, 6));
    EXPECT_EQ(last_move,         glm::ivec2(9, 10));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        1u);
    EXPECT_EQ(wheel_count,       1u);
}

TEST(InputSystem, inject_keyboard_events)
{
    auto engine = ice::Engine{};

    engine.start_system<ice::InputSystem>();

    auto* input = engine.get_system<ice::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto* keyboard = input->get_keyboard();
    ASSERT_NE(nullptr, keyboard);

    auto last_mod       = ice::KeyMod::NONE;
    auto last_key       = ice::Key::UNDEFINED;
    auto last_text      = std::string();
    auto key_down_count = 0u;
    auto key_up_count   = 0u;
    auto text_count     = 0u;
    keyboard->on_key_down([&] (auto mod, auto key) {
        last_mod = mod;
        last_key = key;
        key_down_count++;
    });
    keyboard->on_key_up([&] (auto mod, auto key) {
        last_mod = mod;
        last_key = key;
        key_up_count++;
    });
    keyboard->on_text([&] (auto text) {
        last_text = text;
        text_count++;
    });

    input->inject_key_down(ice::KeyMod::CTRL, ice::Key::C);
    engine.tick();

    EXPECT_EQ(last_mod       , ice::KeyMod::CTRL);
    EXPECT_EQ(last_key       , ice::Key::C);
    EXPECT_EQ(last_text      , "");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 0u);
    EXPECT_EQ(text_count     , 0u);

    input->inject_key_up(ice::KeyMod::ALT, ice::Key::F4);
    engine.tick();

    EXPECT_EQ(last_mod       , ice::KeyMod::ALT);
    EXPECT_EQ(last_key       , ice::Key::F4);
    EXPECT_EQ(last_text      , "");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 1u);
    EXPECT_EQ(text_count     , 0u);

    input->inject_text("c");
    engine.tick();

    EXPECT_EQ(last_mod       , ice::KeyMod::ALT);
    EXPECT_EQ(last_key       , ice::Key::F4);
    EXPECT_EQ(last_text      , "c");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 1u);
    EXPECT_EQ(text_count     , 1u);

}
