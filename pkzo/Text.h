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
#include <string>
#include <glm/glm.hpp>

#include "Rectangle.h"

namespace pkzo
{
    class Font;
    class Material;
    class Texture;

    //! 2D Text
    class PKZO_EXPORT Text : public Rectangle
    {
    public:
        //! Construct Text
        //!
        //! @{
        Text(const std::string& text, const std::shared_ptr<Font>& font, const std::shared_ptr<Material>& material) noexcept;
        Text(const glm::mat4& transform, const std::string& text, const std::shared_ptr<Font>& font, const std::shared_ptr<Material>& material) noexcept;
        //! @}

        ~Text();

        //! Set the font.
        void set_font(const std::shared_ptr<Font>& value) noexcept;
        //! Get teh font.
        const std::shared_ptr<Font>& get_font() const noexcept;

        //! Set the text.
        void set_text(const std::string& value) noexcept;
        //! Get the text.
        const std::string& get_text() const noexcept;

        //! Set the material.
        void set_material(const std::shared_ptr<Material>& value) noexcept;

    protected:
        void update(std::chrono::milliseconds dt) noexcept override;

    private:
        std::shared_ptr<Font>     font;
        std::string               text;
        std::shared_ptr<Material> base_material;
        bool                      dirty    = false;
    };
}

