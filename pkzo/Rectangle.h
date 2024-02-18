// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include "ScreenNode.h"

#include "Image.h"

namespace pkzo
{
    class PKZO_EXPORT Rectangle : public ScreenNode
    {
    public:
        Rectangle() noexcept;
        explicit Rectangle(const glm::vec2& size) noexcept;
        explicit Rectangle(const glm::vec2& size, const glm::vec4& color) noexcept;
        explicit Rectangle(const glm::vec2& size, const std::shared_ptr<Image>& image) noexcept;
        explicit Rectangle(const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Image>& image) noexcept;
        explicit Rectangle(const glm::mat3& transform, const glm::vec2& size) noexcept;
        explicit Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color) noexcept;
        explicit Rectangle(const glm::mat3& transform, const glm::vec2& size, const std::shared_ptr<Image>& image) noexcept;
        explicit Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Image>& image) noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_image(const std::shared_ptr<Image>& value) noexcept;
        const std::shared_ptr<Image>& get_image() const noexcept;

        //void draw(ScreenRenderer& renderer) const override;

    private:
        glm::vec2              size = glm::vec2(15.0f);
        glm::vec4              color = glm::vec4(1.0f);
        std::shared_ptr<Image> image;
    };
}
