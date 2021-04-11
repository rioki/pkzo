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

namespace pkzo::two::ui
{
    CheckBox::CheckBox() noexcept
    {

        background = std::make_shared<Rectangle>();
        add_node(background);

        hit_area = std::make_shared<HitArea>();
        hit_area->on_click([this] () {
            handle_click();
        });
        add_node(hit_area);
    }

    CheckBox::CheckBox(const std::shared_ptr<Texture>& ct, const std::shared_ptr<Texture>& uct) noexcept
    : CheckBox(ct, uct, false) {}

    CheckBox::CheckBox(const std::shared_ptr<Texture>& ct, const std::shared_ptr<Texture>& uct, bool c) noexcept
    : checked_texture(ct), unchecked_texture(uct), checked(c)
    {
        assert(checked_texture);
        assert(unchecked_texture);
        assert(checked_texture->get_size() == unchecked_texture->get_size());

        background = std::make_shared<Rectangle>(checked ? checked_texture : unchecked_texture);
        add_node(background);

        hit_area = std::make_shared<HitArea>();
        hit_area->set_size(background->get_size());
        hit_area->on_click([this] () {
            handle_click();
        });
        add_node(hit_area);
    }

    CheckBox::~CheckBox() = default;

    const glm::vec2& CheckBox::get_size() const noexcept
    {
        assert(background);
        return background->get_size();
    }

    void CheckBox::set_checked_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        checked_texture = value;
        if (checked)
        {
            background->set_texture(checked_texture);
            hit_area->set_size(background->get_size());
        }
    }

    const std::shared_ptr<Texture>& CheckBox::get_checked_texture() const noexcept
    {
        return checked_texture;
    }

    void CheckBox::set_unchecked_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        unchecked_texture = value;
        if (!checked)
        {
            background->set_texture(checked_texture);
            hit_area->set_size(background->get_size());
        }
    }

    const std::shared_ptr<Texture>& CheckBox::get_unchecked_texture() const noexcept
    {
        return unchecked_texture;
    }

    void CheckBox::set_checked(bool value) noexcept
    {
        checked = value;
        background->set_texture(checked ? checked_texture : unchecked_texture);
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
        background->set_texture(checked ? checked_texture : unchecked_texture);
    }
}
