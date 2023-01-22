// pkzo
// Copyright 2022-2023 Sean Farrell
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
#include "MenuBar.h"

#include "HorizontalLayout.h"

namespace pkzo
{
    MenuBar::MenuBar(const std::shared_ptr<Style>& style)
    : Menu(style)
    {
        background = std::make_shared<Rectangle>(glm::mat3(1.0f), glm::vec2(15.0f, 15.0f), style->get_color("MainMenu", "background_color"), style->get_texture("MainMenu", "background_texture"));
        add_node(background);

        layout = std::make_shared<HorizontalLayout>(5.0f);
        add_node(layout);
    }

    glm::vec2 MenuBar::get_min_size() const noexcept
    {
        // The size of the background is the size of the MainMenu, we can not size smaller.
        // TODO: how do we handle resizing of the window?
        return layout->get_size();
    }

    glm::vec2 MenuBar::handle_size_request(const glm::vec2& value) noexcept
    {
        // this feels like a new layout
        auto size = glm::max(get_min_size(), value);
        layout->set_position(glm::vec2((-size.x / 2.0f) + (layout->get_size().x / 2.0f), 0.0f));
        background->set_size(size);
        return size;
    }
}
