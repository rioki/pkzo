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
#include "KeyInput.h"

namespace pong2d
{
    KeyInput::KeyInput(const glm::mat4& transform, const std::shared_ptr<pkzo::Font>& f, const std::shared_ptr<pkzo::Material>& m, pkzo::Key k) noexcept
    : SceneNodeGroup(transform), key(k)
    {
        text = std::make_shared<pkzo::Text>(to_string(key), f, m);
        add_node(text);

        hit_area = std::make_shared<pkzo::HitArea>(glm::vec3(f->estimate("ESCAPE"), 0.01f));
        hit_area->on_click([this] (auto button)
        {
            if (button == pkzo::MouseButton::LEFT)
            {
                click_signal.emit();
            }
        });
        add_node(hit_area);
    }

    void KeyInput::set_key(pkzo::Key value) noexcept
    {
        key = value;
        text->set_text(to_string(value));
    }

    pkzo::Key KeyInput::get_key() const noexcept
    {
        return key;
    }

    rsig::signal<>& KeyInput::get_click_signal() noexcept
    {
        return click_signal;
    }

    rsig::connection KeyInput::on_click(const std::function<void()>& cb) noexcept
    {
        return click_signal.connect(cb);
    }
}
