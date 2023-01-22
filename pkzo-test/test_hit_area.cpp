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

TEST(HitArea, default_contruct)
{
    auto hitarea = pkzo::HitArea();
    EXPECT_GLM_NEAR(glm::mat3(1.0),   hitarea.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(15.0f), hitarea.get_size(),      1e-4f);
}

TEST(HitArea, init)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);
    EXPECT_GLM_NEAR(transform, hitarea.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(size,      hitarea.get_size(),      1e-4f);
}

TEST(HitArea, left_click_inside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(23.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::LEFT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(23.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 17.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::LEFT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(1u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 17.0f), 1e-4f);
}

TEST(HitArea, middle_click_inside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(23.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::MIDDLE, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(23.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 17.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::MIDDLE, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 17.0f), 1e-4f);
}

TEST(HitArea, right_click_inside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(23.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::RIGHT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(23.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 17.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::RIGHT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(1u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 17.0f), 1e-4f);
}

TEST(HitArea, left_click_outside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::LEFT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::LEFT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, middle_click_outside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::MIDDLE, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::MIDDLE, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, right_click_outside)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::RIGHT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::RIGHT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, left_click_move_out)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(24.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::LEFT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(24.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::LEFT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, middle_click_move_out)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(24.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::MIDDLE, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(24.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::MIDDLE, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, right_click_move_out)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(24.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::RIGHT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, true);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(24.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, -200.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::RIGHT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, false);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, -200.0f), 1e-4f);
}

TEST(HitArea, left_click_move_in)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::LEFT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 16.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::LEFT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::LEFT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 16.0f), 1e-4f);
}

TEST(HitArea, middle_click_move_in)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::MIDDLE, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 16.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::MIDDLE, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::MIDDLE);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 16.0f), 1e-4f);
}

TEST(HitArea, right_click_move_in)
{
    auto transform = glm::mat3(1.0f);
    transform = glm::translate(transform, {-25.0f, 50.0f});
    transform = glm::rotate(transform, glm::radians(35.0f));
    auto size = glm::vec2(150.0f, 35.0f);
    auto hitarea = pkzo::HitArea(transform, size);

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

    auto pos1 = glm::transform(transform, glm::vec2(200.0f, 14.0f));
    hitarea.handle_mouse_down(pkzo::MouseButton::RIGHT, pos1);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(0u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_down_inside, false);
    EXPECT_EQ(mouse_down_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_down_pos, glm::vec2(200.0f, 14.0f), 1e-4f);

    auto pos2 = glm::transform(transform, glm::vec2(24.0f, 16.0f));
    hitarea.handle_mouse_up(pkzo::MouseButton::RIGHT, pos2);

    EXPECT_EQ(1u, mouse_down_count);
    EXPECT_EQ(1u, mouse_up_count);
    EXPECT_EQ(0u, click_count);
    EXPECT_EQ(0u, right_click_count);

    EXPECT_EQ(mouse_up_inside, true);
    EXPECT_EQ(mouse_up_button, pkzo::MouseButton::RIGHT);
    EXPECT_GLM_NEAR(mouse_up_pos, glm::vec2(24.0f, 16.0f), 1e-4f);
}