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

#include "SceneNodeGroup.h"

namespace pkzo
{
    class Material;
    class HitArea;
    class Rectangle;

    //! Check Box
    class PKZO_EXPORT CheckBox : public SceneNodeGroup
    {
    public:
        CheckBox(const glm::vec2& size, const std::shared_ptr<Material>& checked_material, const std::shared_ptr<Material>& unchecked_material, bool checked) noexcept;

        ~CheckBox();

        //! Set the check box size.
        void set_size(const glm::vec2& value) const noexcept;
        const glm::vec2& get_size() const noexcept;

        void set_checked_material(const std::shared_ptr<Material>& value) noexcept;
        const std::shared_ptr<Material>& get_checked_material() const noexcept;

        void set_unchecked_material(const std::shared_ptr<Material>& value) noexcept;
        const std::shared_ptr<Material>& get_unchecked_material() const noexcept;

        void set_checked(bool value) noexcept;
        bool get_checked() const noexcept;

        void on_change(const std::function<void (bool)>& cb) noexcept;

    private:
        bool checked = false;
        std::shared_ptr<Material> unchecked_material;
        std::shared_ptr<Material> checked_material;

        std::shared_ptr<Rectangle> background;
        std::shared_ptr<HitArea>   hit_area;

        std::function<void (bool)> change_cb;

        void handle_click();
    };
}

