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
#include "CheckBox.h"

#include "Texture.h"
#include "Rectangle.h"
#include "HitArea.h"

namespace pkzo
{
    CheckBox::CheckBox(const glm::vec2& size, const std::shared_ptr<Material>& cm, const std::shared_ptr<Material>& ucm, bool c) noexcept
    : checked_material(cm), unchecked_material(ucm), checked(c)
    {
        DBG_ASSERT(checked_material);
        DBG_ASSERT(unchecked_material);

        background = std::make_shared<Rectangle>(size, checked ? checked_material : unchecked_material);
        add_node(background);

        hit_area = std::make_shared<HitArea>(glm::vec3(size, 0.01f));
        hit_area->on_click([this] (auto button) {
            handle_click();
        });
        add_node(hit_area);
    }

    CheckBox::~CheckBox() = default;

    void CheckBox::set_size(const glm::vec2& value) const noexcept
    {
        DBG_ASSERT(background);
        DBG_ASSERT(hit_area);
        background->set_size(value);
        hit_area->set_size(glm::vec3(value, 0.01f));
    }

    const glm::vec2& CheckBox::get_size() const noexcept
    {
        DBG_ASSERT(background);
        return background->get_size();
    }

    void CheckBox::set_checked_material(const std::shared_ptr<Material>& value) noexcept
    {
        checked_material = value;
        if (checked)
        {
            background->set_material(checked_material);
        }
    }

    const std::shared_ptr<Material>& CheckBox::get_checked_material() const noexcept
    {
        return checked_material;
    }

    void CheckBox::set_unchecked_material(const std::shared_ptr<Material>& value) noexcept
    {
        unchecked_material = value;
        if (!checked)
        {
            background->set_material(checked_material);
        }
    }

    const std::shared_ptr<Material>& CheckBox::get_unchecked_material() const noexcept
    {
        return unchecked_material;
    }

    void CheckBox::set_checked(bool value) noexcept
    {
        checked = value;
        background->set_material(checked ? checked_material : unchecked_material);
    }

    bool CheckBox::get_checked() const noexcept
    {
        return checked;
    }

    void CheckBox::on_change(const std::function<void(bool)>& cb) noexcept
    {
        change_cb = cb;
    }

    void CheckBox::handle_click()
    {
        checked = !checked;
        if (change_cb)
        {
            change_cb(checked);
        }
        background->set_material(checked ? checked_material : unchecked_material);
    }
}
