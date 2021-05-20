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
#include <glm/glm.hpp>

#include "SceneNodeGroup.h"

namespace pkzo
{
    class Rectangle;
    class Text;
    class HitArea;
    class Material;
    class Font;

    //! 2D Button
    class PKZO_EXPORT Button : public SceneNodeGroup
    {
    public:
        //! Construct Button
        //!
        //! @param caption the button caption
        //! @param size the size of the button
        //! @param background_material
        //! @param text_material
        //! @param font
        //!
        //! @{
        Button(const std::string& caption, const glm::vec2& size, const std::shared_ptr<Material>& background_material, const std::shared_ptr<Material>& text_material, const std::shared_ptr<Font>& font) noexcept;
        Button(const glm::mat4& transform, const std::string& caption, const glm::vec2& size, const std::shared_ptr<Material>& background_material, const std::shared_ptr<Material>& text_material, const std::shared_ptr<Font>& font) noexcept;
        //! @}

        ~Button();

        //! Set the button size.
        void set_size(const glm::vec2& value) const noexcept;
        //! Get the button size.
        glm::vec2 get_size() const noexcept;

        //! Set the caption.
        void set_caption(const std::string& value) noexcept;
        //! Get the caption.
        const std::string& get_caption() const noexcept;

        //! Set the background material.
        void set_background_material(const std::shared_ptr<Material>& value) noexcept;
        //! Get the background material.
        const std::shared_ptr<Material>& get_background_material() const noexcept;

        //! Set the text material.
        void set_text_material(const std::shared_ptr<Material>& value) noexcept;
        //! Get the text material.
        const std::shared_ptr<Material>& get_text_material() const noexcept;

        //! Set the font.
        void set_font(const std::shared_ptr<Font>& value) noexcept;
        //! Get the font.
        const std::shared_ptr<Font>& get_font() const noexcept;

        void on_click(const std::function<void ()>& cb) noexcept;

    private:
        std::shared_ptr<Rectangle> background;
        std::shared_ptr<Text>      caption;
        std::shared_ptr<HitArea>   hit_area;
    };
}
