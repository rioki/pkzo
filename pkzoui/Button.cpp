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
#include "Button.h"

namespace pkzoui
{
    Button::Button() noexcept
    {
        background = std::make_shared<Rectangle>();
        add_node(background);

        caption = std::make_shared<Text>();
        add_node(caption);

        hit_area = std::make_shared<HitArea>();
        add_node(hit_area);
    }

    Button::Button(const std::shared_ptr<Texture>& b, const std::shared_ptr<Font>& cf, const std::string& c) noexcept
    : Button(b, glm::vec4(1.0f), cf, glm::vec4(1.0f), c) {}

    Button::Button(const std::shared_ptr<Texture>& b, const glm::vec4& bc, const std::shared_ptr<Font>& cf, const std::string& c) noexcept
    : Button(b, bc, cf, glm::vec4(1.0f), c) {}

    Button::Button(const std::shared_ptr<Texture>& b, const std::shared_ptr<Font>& cf, const glm::vec4& cc, const std::string& c) noexcept
    : Button(b, glm::vec4(1.0f), cf, cc, c) {}

    Button::Button(const std::shared_ptr<Texture>& b, const glm::vec4& bc, const std::shared_ptr<Font>& cf, const glm::vec4& cc, const std::string& c) noexcept
    {
        assert(b);
        assert(cf);
        background = std::make_shared<Rectangle>(b, bc);
        background->set_size(b->get_size());
        add_node(background);

        caption = std::make_shared<Text>(cf, cc, c);
        add_node(caption);

        hit_area = std::make_shared<HitArea>();
        hit_area->set_size(background->get_size());
        add_node(hit_area);
    }

    Button::~Button() = default;

    void Button::set_caption(const std::string& value) noexcept
    {
        assert(caption);
        caption->set_text(value);
    }

    const std::string& Button::get_caption() const noexcept
    {
        assert(caption);
        return caption->get_text();
    }

    void Button::set_caption_color(const glm::vec4& value) noexcept
    {
        assert(caption);
        caption->set_color(value);
    }

    const glm::vec4& Button::get_caption_color() const noexcept
    {
        assert(caption);
        return caption->get_color();
    }

    void Button::set_caption_font(const std::shared_ptr<Font>& value) noexcept
    {
        assert(caption);
        caption->set_font(value);
    }

    const std::shared_ptr<Font>& Button::get_caption_font() const noexcept
    {
        assert(caption);
        return caption->get_font();
    }

    void Button::set_background(const std::shared_ptr<Texture>& value) noexcept
    {
        assert(background);
        background->set_texture(value);
        background->set_size(value->get_size());
        hit_area->set_size(background->get_size());
    }

    const std::shared_ptr<Texture>& Button::get_background() const noexcept
    {
        assert(background);
        return background->get_texture();
    }

    void Button::set_background_color(const glm::vec4& value) noexcept
    {
        assert(background);
        background->set_color(value);
    }

    const glm::vec4& Button::get_background_color() const noexcept
    {
        assert(background);
        return background->get_color();
    }

    void Button::on_click(const std::function<void()>& cb) noexcept
    {
        assert(hit_area);
        hit_area->on_click(cb);
    }
}
