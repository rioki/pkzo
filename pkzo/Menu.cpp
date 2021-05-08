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
#include "Menu.h"

#include "Rectangle.h"
#include "Button.h"

namespace pkzo
{
    Menu::Menu(const std::shared_ptr<pkzo::Texture>& top_texture, const std::shared_ptr<pkzo::Texture>& body_texture, const std::shared_ptr<pkzo::Texture>& bottom_texture, const std::shared_ptr<Font>& font, const glm::vec4& text_color, const std::vector<std::string>& options) noexcept
    {
        // create
        top = std::make_shared<Rectangle>(top_texture);
        add_node(top);

        for (auto i = 0u; i < options.size(); i++)
        {
            auto body = std::make_shared<Button>(body_texture, font, text_color, options[i]);
            bodies.push_back(body);
            body->on_click([this, i] () {
                if (select_cb)
                {
                    select_cb(i);
                }
            });
            add_node(body);
        }

        bottom = std::make_shared<Rectangle>(bottom_texture);
        add_node(bottom);

        // layout
        auto size = get_size();
        top->set_position({0.0, size.y / 2.0f - top->get_size().y / 2.0f});
        auto pos = size.y / 2.0f - top->get_size().y;
        for (auto& body : bodies)
        {
            auto bs = body->get_size().y;
            body->set_position({0.0, pos - bs / 2.0f});
            pos -= bs;
        }
        bottom->set_position({0.0, -size.y / 2.0f + bottom->get_size().y / 2.0f});
    }

    Menu::~Menu() = default;

    glm::vec2 Menu::get_size() const noexcept
    {
        auto result = glm::vec2(0.0f);

        assert(top);
        auto ts = top->get_size();
        result.x = std::max(result.x, ts.x);
        result.y += ts.y;

        for (auto& body : bodies)
        {
            assert(body);
            auto bs = body->get_size();
            result.x = std::max(result.x, bs.x);
            result.y += bs.y;
        }

        assert(bottom);
        auto bs = bottom->get_size();
        result.x = glm::max(result.x, bs.x);
        result.y += bs.y;

        return result;
    }

    void Menu::on_select(const std::function<void(size_t)>& cb)
    {
        select_cb = cb;
    }
}
