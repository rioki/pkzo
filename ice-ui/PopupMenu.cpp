// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "PopupMenu.h"

#include "VerticalLayout.h"

namespace ice::ui
{
    PopupMenu::PopupMenu(const std::shared_ptr<Style>& style)
    : PopupMenu(glm::vec2(0.0f), style) {}

    PopupMenu::PopupMenu(const glm::vec2& position, const std::shared_ptr<Style>& style)
    : Menu(position, style)
    {
        background = std::make_shared<Rectangle>(glm::mat3(1.0f), glm::vec2(15.0f, 15.0f), style->get_color("MainMenu", "background_color"), style->get_texture("MainMenu", "background_texture"));
        add_node(background);

        layout = std::make_shared<VerticalLayout>(2.0f);
        add_node(layout);

        hit_area = std::make_shared<HitArea>(background->get_size());
        add_node(hit_area);

        hit_area->on_mouse_up([this] (auto in, auto button, auto pos) {
            if (!in) {
                click_out_signal.emit();
            }
        });
    }

    [[nodiscard]] rsig::signal<>& PopupMenu::get_click_out_signal() noexcept
    {
        return click_out_signal;
    }

    rsig::connection PopupMenu::on_click_out(const std::function<void ()>& cb) noexcept
    {
        return click_out_signal.connect(cb);
    }

    glm::vec2 PopupMenu::get_min_size() const noexcept
    {
        return layout->get_size();
    }

    glm::vec2 PopupMenu::handle_size_request(const glm::vec2& value) noexcept
    {
        layout->set_size(value);
        background->set_size(layout->get_size());
        hit_area->set_size(layout->get_size());
        return layout->get_size();
    }
}
