// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Screen.h"

namespace ice
{
    Screen::Screen(const glm::vec2& _size)
    : size(_size)
    {
        assert(size.x > 0.0f && size.y > 0.0f);
    }

    Screen::~Screen()
    {
        assert(active == false);
    }

    const glm::vec2& Screen::get_size() const noexcept
    {
        return size;
    }

    void Screen::resize(const glm::vec2& value) noexcept
    {
        assert(value.x > 0.0f && value.y > 0.0f);
        size = value;
    }

    void Screen::activate()
    {
        assert(false == active);
        active = true;

        ScreenNodeGroup::activate();
    }

    void Screen::deactivate()
    {
        assert(true == active);

        ScreenNodeGroup::deactivate();

        active   = false;
    }

    bool Screen::is_active() const noexcept
    {
        return active;
    }

    template <typename T>
    T map(T source_left, T source_right, T target_left, T target_right, T value)
    {
        auto source_range = source_right - source_left;
        auto target_range = target_right - target_left;
        return (value - source_left) * (target_range / source_range) + target_left;
    }

    glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos)
    {
        auto hss = screen_size / 2.0f;
        return {
            map<float>(0.0f, win_size.x, -hss.x,  hss.x, pos.x),
            map<float>(0.0f, win_size.y,  hss.y, -hss.y, pos.y)
        };
    }
}
