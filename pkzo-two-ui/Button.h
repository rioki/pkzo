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

#ifndef _PKZO_TWO_UI_BUTTON_H_
#define _PKZO_TWO_UI_BUTTON_H_

#include "config.h"

#include <memory>
#include <pkzo/pkzo.h>
#include <pkzo-two/pkzo-two.h>

namespace pkzo::two::ui
{
    class PKZOUI_EXPORT Button : public ScreenNodeGroup
    {
    public:
        Button() noexcept;

        Button(const std::shared_ptr<Texture>& background) noexcept;
        Button(const std::shared_ptr<Texture>& background, const std::shared_ptr<Font>& caption_font, const std::string& caption) noexcept;
        Button(const std::shared_ptr<Texture>& background, const glm::vec4& background_color, const std::shared_ptr<Font>& caption_font, const std::string& caption) noexcept;
        Button(const std::shared_ptr<Texture>& background, const std::shared_ptr<Font>& caption_font, const glm::vec4& caption_color, const std::string& caption) noexcept;
        Button(const std::shared_ptr<Texture>& background, const glm::vec4& background_color, const std::shared_ptr<Font>& caption_font, const glm::vec4& caption_color, const std::string& caption) noexcept;

        ~Button();

        glm::vec2 get_size() const noexcept;

        void set_caption(const std::string& value) noexcept;
        const std::string& get_caption() const noexcept;

        void set_caption_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_caption_color() const noexcept;

        void set_caption_font(const std::shared_ptr<Font>& value) noexcept;
        const std::shared_ptr<Font>& get_caption_font() const noexcept;

        void set_background(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_background() const noexcept;

        void set_background_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_background_color() const noexcept;

        void on_click(const std::function<void ()>& cb) noexcept;

    private:
        std::shared_ptr<Text>      caption;
        std::shared_ptr<Rectangle> background;
        std::shared_ptr<HitArea>   hit_area;
    };
}

#endif
