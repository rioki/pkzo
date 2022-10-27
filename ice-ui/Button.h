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

#pragma once
#include "config.h"

#include <ice/ScreenNodeGroup.h>
#include <ice/Rectangle.h>
#include <ice/Text.h>

namespace ice::ui
{
    class ICE_EXPORT Button : public ScreenNodeGroup
    {
    public:
        Button();
        Button(const glm::mat3& transform, const glm::vec2& size, const std::string& label_text, const std::shared_ptr<Font>& font, const glm::vec4& label_color, const std::shared_ptr<Texture> background_texture, const glm::vec4& background_color);

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_label_text(const std::string& value) noexcept;
        const std::string& get_label_text() const noexcept;

        void set_label_font(const std::shared_ptr<Font>& value) noexcept;
        const std::shared_ptr<Font>& get_label_font() const noexcept;

        void set_label_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_label_color() const noexcept;

        void set_background_texture(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_background_texture() const noexcept;

        void set_background_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_background_color() const noexcept;

        rsig::connection on_click(const std::function<void ()>& cb) noexcept;
        rsig::signal<>& get_click_signal() noexcept;

    private:
        Rectangle background;
        Text      label;
        HitArea   hit_area;
    };
}
