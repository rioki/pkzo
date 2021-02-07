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

namespace pkzoui
{
    Slider::Slider() noexcept
    {
        background = std::make_shared<Rectangle>();
        add_node(background);

        handle = std::make_shared<Rectangle>();
        add_node(handle);

        hit_area = std::make_shared<HitArea>();
        hit_area->on_mouse_down([this] (auto button, auto pos) {
            handle_down(button, pos);
        });
        hit_area->on_mouse_move([this] (auto pos) {
            handle_move(pos);
        });
        hit_area->on_mouse_up([this] (auto button, auto pos) {
            handle_up(button, pos);
        });
        add_node(hit_area);
    }

    Slider::Slider(const std::shared_ptr<Texture>& bt, const std::shared_ptr<Texture>& ht) noexcept
    : Slider(bt, ht, 0.5f) {}

    Slider::Slider(const std::shared_ptr<Texture>& bt, const std::shared_ptr<Texture>& ht, float v) noexcept
    : value(v)
    {
        assert(bt);
        assert(ht);
        if (bt->get_size().x == ht->get_size().x)
        {
            orientation = SliderOrientation::VERTICAL;
        }
        else if (bt->get_size().y == ht->get_size().y)
        {
            orientation = SliderOrientation::HORIZONTAL;
        }
        else
        {
            assert(false);
        }

        background = std::make_shared<Rectangle>(bt);
        add_node(background);

        handle = std::make_shared<Rectangle>(ht);
        add_node(handle);

        hit_area = std::make_shared<HitArea>();
        hit_area->set_size(background->get_size());
        hit_area->on_mouse_down([this] (auto button, auto pos) {
            handle_down(button, pos);
        });
        hit_area->on_mouse_move([this] (auto pos) {
            handle_move(pos);
        });
        hit_area->on_mouse_up([this] (auto button, auto pos) {
            handle_up(button, pos);
        });
        add_node(hit_area);

        update_hadle_position();
    }

    Slider::~Slider() = default;

    const glm::vec2& Slider::get_size() const noexcept
    {
        assert(background);
        return background->get_size();
    }

    void Slider::set_background_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        assert(background);
        assert(hit_area);
        background->set_texture(value);
        hit_area->set_size(background->get_size());
    }

    const std::shared_ptr<Texture>& Slider::get_background_texture() const noexcept
    {
        assert(background);
        return background->get_texture();
    }

    void Slider::set_handle_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        assert(handle);
        handle->set_texture(value);
    }

    const std::shared_ptr<Texture>& Slider::get_handle_texture() const noexcept
    {
        assert(handle);
        return handle->get_texture();
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
        assert(background);
        assert(handle);

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

        handle->set_position(hp);
    }

    void Slider::set_value_from_pos(glm::vec2 pos)
    {
        auto bs = background->get_size();
        auto hs = handle->get_size();

        if (orientation == SliderOrientation::HORIZONTAL)
        {
            auto l  = bs.x - hs.x;
            auto hl = l / 2.0f;
            value = glm::clamp((pos.x + hl) / l, 0.0f, 1.0f);
        }
        else
        {
            auto l  = bs.y - hs.y;
            auto hl = l / 2.0f;
            value = glm::clamp((pos.y + hl) / l, 0.0f, 1.0f);
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
