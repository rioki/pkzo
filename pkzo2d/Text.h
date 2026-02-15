// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Shape.h"

#include <pkzo/Font.h>

namespace pkzo2d
{
    using pkzo::Font;

    class PKZO2D_EXPORT Text : public Shape
    {
    public:
        struct Specs
        {
            Node*                    parent    = nullptr;
            glm::mat3                transform = glm::mat3(1.0f);
            std::u8string            text      = u8"Text";
            glm::vec4                color     = glm::vec4(1.0f);
            std::shared_ptr<Font>    font;
            unsigned int             font_size = 12;
        };

        Text(Specs specs);

        ~Text();

        glm::vec2 get_size() const;

        void set_text(const std::u8string& value);
        const std::u8string& get_text() const;

        void set_color(const glm::vec4& value);

        void set_font(const std::shared_ptr<Font>& value);
        const std::shared_ptr<Font>& get_font() const;

        void set_font_size(unsigned int value);
        unsigned int get_font_size() const;

        glm::mat4 get_model_matrix() const override;
        std::shared_ptr<Mesh> get_mesh() const override;
        glm::vec4 get_color() const override;
        std::shared_ptr<Texture> get_texture() const override;

    private:
        glm::vec4             color;
        std::u8string         text;
        std::shared_ptr<Font> font;
        unsigned int          font_size;

        mutable std::shared_ptr<Mesh>    mesh;
        mutable std::shared_ptr<Texture> texture;
    };
}
