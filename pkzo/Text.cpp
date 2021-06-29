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
#include "Text.h"

#include "Pipeline.h"
#include "Font.h"
#include "Material.h"

namespace pkzo
{
    auto safe_estimate(const std::shared_ptr<Font>& font, const std::string& text)
    {
        DBG_ASSERT(font);
        if (font)
        {
            return glm::vec2(font->estimate(text));
        }
        else
        {
            return glm::vec2(1.0f);
        }
    }

    auto make_rectangle_material(const std::shared_ptr<Font>& font, const std::string& text, const std::shared_ptr<Material>& material)
    {
        DBG_ASSERT(font);
        DBG_ASSERT(material);
        if (font)
        {
            auto text_mask = font->render(text);
            auto material_copy = std::make_shared<Material>(*material);
            material_copy->set_mask(text_mask);
            return material_copy;
        }
        else
        {
            return material;
        }
    }

    Text::Text(const std::string& t, const std::shared_ptr<Font>& f, const std::shared_ptr<Material>& m) noexcept
    : Rectangle(safe_estimate(f, t), make_rectangle_material(f, t, m)), font(f), text(t), base_material(m) {}

    Text::Text(const glm::mat4& transform, const std::string& t, const std::shared_ptr<Font>& f, const std::shared_ptr<Material>& m) noexcept
    : Rectangle(transform, safe_estimate(f, t), make_rectangle_material(f, t, m)), font(f), text(t), base_material(m) {}

    Text::~Text() = default;

    void Text::set_font(const std::shared_ptr<Font>& value) noexcept
    {
        DBG_ASSERT(value);
        font = value;
        dirty = true;
    }

    const std::shared_ptr<Font>& Text::get_font() const noexcept
    {
        return font;
    }

    void Text::set_text(const std::string& value) noexcept
    {
        text = value;
        dirty = true;
    }

    const std::string& Text::get_text() const noexcept
    {
        return text;
    }

    // REVIEW: because this function on Rectangle is not virtual, it may not be called
    // when you have a pointer to base. This may result some confusion as to what happens.
    void Text::set_material(const std::shared_ptr<Material>& value) noexcept
    {
        DBG_ASSERT(value);
        base_material = value;
        dirty = true;
    }

    void Text::update(std::chrono::milliseconds dt) noexcept
    {
        if (dirty)
        {
            DBG_ASSERT(font);
            DBG_ASSERT(base_material);
            set_size(safe_estimate(font, text));
            Rectangle::set_material(make_rectangle_material(font, text, base_material));
            dirty = false;
        }
        Rectangle::update(dt);
    }
}
