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

#pragma once

#include "config.h"

#include <memory>
#include <list>
#include <glm/glm.hpp>
#include <pkzo/Texture.h>

#include "ScreenNode.h"

namespace pkzo
{
    class PKZO_EXPORT Rectangle : public ScreenNode
    {
    public:
        Rectangle() noexcept;
        Rectangle(const std::shared_ptr<Texture>& texture) noexcept;
        Rectangle(const std::shared_ptr<Texture>& texture, const glm::vec2& size) noexcept;
        Rectangle(const glm::vec4& color, const glm::vec2& size) noexcept;
        Rectangle(const std::shared_ptr<Texture>& texture, const glm::vec4& color) noexcept;
        Rectangle(const std::shared_ptr<Texture>& texture, const glm::vec4& color, const glm::vec2& size) noexcept;
        ~Rectangle();

        void set_position(const glm::vec2& value) noexcept;
        const glm::vec2& get_position() const noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_texture(const std::shared_ptr<Texture>& value);
        const std::shared_ptr<Texture>& get_texture() const;

    private:
        void render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept override;

    private:
        glm::vec2                position = glm::vec2(0.0f);
        std::shared_ptr<Texture> texture;
        glm::vec4                color    = glm::vec4(1.0f);
        glm::vec2                size     = glm::vec2(15.0f);
    };
}
