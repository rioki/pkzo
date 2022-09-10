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

#include "ScreenNode.h"
#include "Texture.h"
#include "Font.h"
#include "ScreenRenderer.h"


namespace ice
{
    class ICE_EXPORT Text : public ScreenNode
    {
    public:
        Text(const glm::mat3& transform, const std::string& text, const std::shared_ptr<Font>& font) noexcept;
        Text(const glm::mat3& transform, const std::string& text, const std::shared_ptr<Font>& font, const glm::vec4& color) noexcept;

        glm::vec2 get_size() const noexcept;

        void set_text(const std::string& value) noexcept;
        const std::string& get_text() const noexcept;

        void set_color(const glm::vec4& value) noexcept;
        const glm::vec4& get_color() const noexcept;

        void set_font(const std::shared_ptr<Font>& value) noexcept;
        const std::shared_ptr<Font>& get_font() const noexcept;

        void activate() override;
        void deactivate() override;

    private:
        std::string                text;
        std::shared_ptr<Font>      font;
        glm::vec4                  color     = {1.0f, 1.0f, 1.0f, 1.0f};
        std::shared_ptr<Texture>   texture;

        ScreenRenderer::Rectangle* render_handle = nullptr;
    };
}