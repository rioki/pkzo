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

TEST(SdlInputSystem, has_devices_after_load)
{
    auto engine = pkzo::Engine{};

    engine.start_system<pkzo::SdlInputSystem>();

    const auto* is = engine.get_system<pkzo::InputSystem>();
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

TEST(SdlInputSystem, inject_mouse_events)
{
    auto engine = pkzo::Engine{};

    engine.start_system<pkzo::SdlInputSystem>();

    auto* input = engine.get_system<pkzo::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto* mouse = input->get_mouse();
    ASSERT_NE(nullptr, mouse);

    auto last_button       = pkzo::MouseButton::NONE;
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

    input->inject_mouse_button_down(pkzo::MouseButton::LEFT, glm::ivec2(1, 2));
    engine.tick();

    EXPECT_EQ(last_button,       pkzo::MouseButton::LEFT);
    EXPECT_EQ(last_position,     glm::ivec2(1, 2));
    EXPECT_EQ(last_move,         glm::ivec2(0));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   0u);
    EXPECT_EQ(move_count,        0u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_button_up(pkzo::MouseButton::RIGHT, glm::ivec2(3, 4));
    engine.tick();

    EXPECT_EQ(last_button,       pkzo::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(3, 4));
    EXPECT_EQ(last_move,         glm::ivec2(0));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        0u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_move(glm::ivec2(5, 6), glm::ivec2(7, 8));
    engine.tick();

    EXPECT_EQ(last_button,       pkzo::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(5, 6));
    EXPECT_EQ(last_move,         glm::ivec2(7, 8));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        1u);
    EXPECT_EQ(wheel_count,       0u);

    input->inject_mouse_wheel(glm::ivec2(9, 10));
    engine.tick();

    EXPECT_EQ(last_button,       pkzo::MouseButton::RIGHT);
    EXPECT_EQ(last_position,     glm::ivec2(5, 6));
    EXPECT_EQ(last_move,         glm::ivec2(9, 10));
    EXPECT_EQ(button_down_count, 1u);
    EXPECT_EQ(button_up_count,   1u);
    EXPECT_EQ(move_count,        1u);
    EXPECT_EQ(wheel_count,       1u);
}

TEST(SdlInputSystem, inject_keyboard_events)
{
    auto engine = pkzo::Engine{};

    engine.start_system<pkzo::SdlInputSystem>();

    auto* input = engine.get_system<pkzo::InputSystem>();
    ASSERT_NE(nullptr, input);

    auto* keyboard = input->get_keyboard();
    ASSERT_NE(nullptr, keyboard);

    auto last_mod       = pkzo::KeyMod::NONE;
    auto last_key       = pkzo::Key::UNDEFINED;
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

    input->inject_key_down(pkzo::KeyMod::CTRL, pkzo::Key::C);
    engine.tick();

    EXPECT_EQ(last_mod       , pkzo::KeyMod::CTRL);
    EXPECT_EQ(last_key       , pkzo::Key::C);
    EXPECT_EQ(last_text      , "");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 0u);
    EXPECT_EQ(text_count     , 0u);

    input->inject_key_up(pkzo::KeyMod::ALT, pkzo::Key::F4);
    engine.tick();

    EXPECT_EQ(last_mod       , pkzo::KeyMod::ALT);
    EXPECT_EQ(last_key       , pkzo::Key::F4);
    EXPECT_EQ(last_text      , "");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 1u);
    EXPECT_EQ(text_count     , 0u);

    input->inject_text("c");
    engine.tick();

    EXPECT_EQ(last_mod       , pkzo::KeyMod::ALT);
    EXPECT_EQ(last_key       , pkzo::Key::F4);
    EXPECT_EQ(last_text      , "c");
    EXPECT_EQ(key_down_count , 1u);
    EXPECT_EQ(key_up_count   , 1u);
    EXPECT_EQ(text_count     , 1u);

}
