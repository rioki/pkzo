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

#pragma once
#include "config.h"

#include "ScreenNode.h"

namespace pkzo
{
    class Texture;
    class Renderer;

    class ICE_EXPORT Rectangle : public ScreenNode
    {
    public:
        Rectangle();
        Rectangle(const glm::mat3& transform);
        Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color) noexcept;
        Rectangle(const glm::mat3& transform, const glm::vec2& size, const std::shared_ptr<Texture>& texture) noexcept;
        Rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture) noexcept;

        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_texture(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_texture() const noexcept;

        void activate() override;
        void deactivate() override;

    private:
        glm::vec2                  size      = {15.0f, 15.0f};
        glm::vec4                  color     = {1.0f, 1.0f, 1.0f, 1.0f};
        std::shared_ptr<Texture>   texture;

        Renderer* renderer = nullptr;
        unsigned int render_handle = 0;

        glm::mat3 get_aligned_transform() const noexcept;
    };
}
