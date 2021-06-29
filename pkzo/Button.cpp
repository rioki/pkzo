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

#include "Rectangle.h"
#include "Text.h"
#include "HitArea.h"

using namespace std::literals::string_literals;

namespace pkzo
{
    Button::Button(const glm::vec2& size, const std::shared_ptr<Material>& background_material) noexcept
    : Button(glm::mat4(1.0f), size, background_material) {}

    Button::Button(const glm::mat4& transform, const glm::vec2& size, const std::shared_ptr<Material>& background_material) noexcept
    : Button(transform, "", size, background_material, nullptr, nullptr) {}


    Button::Button(const std::string& caption, const glm::vec2& size, const std::shared_ptr<Material>& background_material, const std::shared_ptr<Material>& text_material, const std::shared_ptr<Font>& font) noexcept
    : Button(glm::mat4(1.0f), caption, size, background_material, text_material, font) {}

    Button::Button(const glm::mat4& transform, const std::string& c, const glm::vec2& size, const std::shared_ptr<Material>& background_material, const std::shared_ptr<Material>& text_material, const std::shared_ptr<Font>& font) noexcept
    : SceneNodeGroup(transform)
    {
        assert(glm::all(glm::greaterThan(size, glm::vec2(0.0f))));
        assert(background_material);

        background = std::make_shared<Rectangle>(size, background_material);
        add_node(background);

        if (text_material && font) 
        {
            caption = std::make_shared<Text>(c, font, text_material);
            add_node(caption);
        }
        
        hit_area = std::make_shared<HitArea>(glm::vec3(size, 1.0f));
        hit_area->on_click([this] (auto button)
        {
            if (button == pkzo::MouseButton::LEFT)
            {
                click_signal.emit();
            }
        });
        add_node(hit_area);
    }

    Button::~Button() = default;

    void Button::set_size(const glm::vec2& value) const noexcept
    {
        DBG_ASSERT(background);
        background->set_size(value);
    }

    glm::vec2 Button::get_size() const noexcept
    {
        DBG_ASSERT(background);
        return background->get_size();
    }

    void Button::set_caption(const std::string& value) noexcept
    {
        DBG_ASSERT(caption);
        caption->set_text(value);
    }

    const std::string& Button::get_caption() const noexcept
    {
        DBG_ASSERT(caption);
        return caption->get_text();
    }

    void Button::set_background_material(const std::shared_ptr<Material>& value) noexcept
    {
        DBG_ASSERT(background);
        background->set_material(value);
    }

    const std::shared_ptr<Material>& Button::get_background_material() const noexcept
    {
        DBG_ASSERT(background);
        return background->get_material();
    }

    void Button::set_text_material(const std::shared_ptr<Material>& value) noexcept
    {
        DBG_ASSERT(caption);
        caption->set_material(value);
    }

    const std::shared_ptr<Material>& Button::get_text_material() const noexcept
    {
        DBG_ASSERT(caption);
        return caption->get_material();
    }

    void Button::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        DBG_ASSERT(caption);
        caption->set_font(value);
    }

    const std::shared_ptr<Font>& Button::get_font() const noexcept
    {
        DBG_ASSERT(caption);
        return caption->get_font();
    }

    rsig::signal<>& Button::get_click_signal() noexcept
    {
        return click_signal;
    }

    rsig::connection Button::on_click(const std::function<void()>& cb) noexcept
    {
        return click_signal.connect(cb);
    }
}
