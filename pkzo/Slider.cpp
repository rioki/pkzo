//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
#include "Slider.h"

#include "Rectangle.h"
#include "HitArea.h"

namespace pkzo
{
    Slider::Slider(const glm::mat4& transform, SliderOrientation o, const glm::vec2& s, const std::shared_ptr<Material>& bm, const glm::vec2& hs, const std::shared_ptr<Material>& hm, float v) noexcept
    : SceneNodeGroup(transform), orientation(o), value(v)
    {
        background = std::make_shared<Rectangle>(s, bm);
        add_node(background);

        handle = std::make_shared<Rectangle>(hs, hm);
        add_node(handle);

        hit_area = std::make_shared<HitArea>(glm::vec3(s, 0.01f));
        hit_area->on_mouse_down([this] (auto pos, auto button) {
            handle_down(button, pos);
        });
        hit_area->on_mouse_move([this] (auto pos, auto mov) {
            handle_move(pos);
        });
        hit_area->on_mouse_up([this] (auto pos, auto button) {
            handle_up(button, pos);
        });
        add_node(hit_area);

        update_hadle_position();
    }

    Slider::~Slider() = default;

    void Slider::set_size(const glm::vec2& value) noexcept
    {
        DBG_ASSERT(background);
        background->set_size(value);
        DBG_ASSERT(hit_area);
        hit_area->set_size(glm::vec3(value, 0.01f));
    }

    const glm::vec2& Slider::get_size() const noexcept
    {
        DBG_ASSERT(background);
        return background->get_size();
    }

    void Slider::set_background_material(const std::shared_ptr<Material>& value) noexcept
    {
        DBG_ASSERT(background);
        background->set_material(value);
    }

    const std::shared_ptr<Material>& Slider::get_background_material() const noexcept
    {
        DBG_ASSERT(background);
        return background->get_material();
    }

    void Slider::set_handle_size(const glm::vec2& value) noexcept
    {
        DBG_ASSERT(handle);
        handle->set_size(value);
    }

    const glm::vec2& Slider::get_handle_size() const noexcept
    {
        DBG_ASSERT(handle);
        return handle->get_size();
    }

    void Slider::set_handle_material(const std::shared_ptr<Material>& value) noexcept
    {
        DBG_ASSERT(handle);
        handle->set_material(value);
    }

    const std::shared_ptr<Material>& Slider::get_handle_material() const noexcept
    {
        DBG_ASSERT(handle);
        return handle->get_material();
    }

    void Slider::set_orientation(SliderOrientation value) noexcept
    {
        orientation = value;
    }

    SliderOrientation Slider::get_orientation() const noexcept
    {
        return orientation;
    }

    void Slider::set_value(float v) noexcept
    {
        value = v;
        update_hadle_position();
    }

    float Slider::get_value() const noexcept
    {
        return value;
    }

    void Slider::on_change(const std::function<void (float)>& cb) noexcept
    {
        change_cb = cb;
    }

    void Slider::update_hadle_position()
    {
        DBG_ASSERT(background);
        DBG_ASSERT(handle);

        auto bs = background->get_size();
        auto hs = handle->get_size();
        auto hp = glm::vec2(0.0f);

        if (orientation == SliderOrientation::HORIZONTAL)
        {
            auto l = bs.x - hs.x;
            auto hl = l / 2.0f;
            hp.x = -hl + l * value;
        }
        else
        {
            auto l = bs.y - hs.y;
            auto hl = l / 2.0f;
            hp.y = -hl + l * value;
        }

        handle->set_transform(glm::translate(glm::mat4(1.0f), {hp.x, hp.y, 0.0f}));
    }

    void Slider::set_value_from_pos(glm::vec2 pos)
    {
        auto bs = background->get_size();
        auto hs = handle->get_size();
        auto iws = glm::inverse(get_world_transform());
        auto lp = iws * glm::vec4(pos, 0.0f, 1.0f);

        if (orientation == SliderOrientation::HORIZONTAL)
        {
            auto l  = bs.x - hs.x;
            auto hl = l / 2.0f;
            value = glm::clamp((lp.x + hl) / l, 0.0f, 1.0f);
        }
        else
        {
            auto l  = bs.y - hs.y;
            auto hl = l / 2.0f;
            value = glm::clamp((lp.y + hl) / l, 0.0f, 1.0f);
        }
    }

    void Slider::handle_down(MouseButton button, glm::vec2 pos)
    {
        if (button == MouseButton::LEFT)
        {
            slide_armed = true;
            set_value_from_pos(pos);
            update_hadle_position();
        }

    }

    void Slider::handle_move(glm::vec2 pos)
    {
        if (slide_armed)
        {
            set_value_from_pos(pos);
            update_hadle_position();
        }
    }

    void Slider::handle_up(MouseButton button, glm::vec2 pos)
    {
        if (button == MouseButton::LEFT)
        {
            slide_armed = false;
        }
    }
}
