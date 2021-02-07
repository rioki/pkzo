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

#ifndef _PKZO2D_TEXT_H_
#define _PKZO2D_TEXT_H_

#include "config.h"

#include <memory>
#include <list>
#include <glm/glm.hpp>
#include <pkzo/Font.h>

#include "ScreenNode.h"

namespace pkzo2d
{
    using namespace pkzo;

    class PKZO2D_EXPORT Text : public ScreenNode
    {
    public:
        Text() noexcept;
        Text(const std::shared_ptr<Font>& font, const std::string& text) noexcept;
        Text(const std::shared_ptr<Font>& font, const glm::vec4& color, const std::string& text) noexcept;
        ~Text();

        void set_position(const glm::vec2& value) noexcept;
        const glm::vec2& get_position() const noexcept;

        void set_font(const std::shared_ptr<Font>& value) noexcept;
        const std::shared_ptr<Font>& get_font() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_text(const std::string& value) noexcept;
        const std::string& get_text() const noexcept;

        glm::vec2 get_size() const noexcept;

    private:
        void render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept override;

    private:
        glm::vec2                position = glm::vec2(0.0f);
        std::shared_ptr<Font>    font;
        glm::vec4                color    = glm::vec4(1.0f);
        std::string              text;
        mutable std::shared_ptr<Texture> texture;
    };
}

#endif
