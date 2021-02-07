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

#ifndef _PKZOUI_CHECK_BOX_H_
#define _PKZOUI_CHECK_BOX_H_

#include "config.h"

#include <memory>
#include <pkzo/pkzo.h>
#include <pkzo2d/pkzo2d.h>

namespace pkzoui
{
    using namespace pkzo;
    using namespace pkzo2d;

    class PKZOUI_EXPORT CheckBox : public ScreenNodeGroup
    {
    public:
        CheckBox() noexcept;

        CheckBox(const std::shared_ptr<Texture>& checked_texture, const std::shared_ptr<Texture>& unchecked_texture) noexcept;
        CheckBox(const std::shared_ptr<Texture>& checked_texture, const std::shared_ptr<Texture>& unchecked_texture, bool checked) noexcept;

        ~CheckBox();

        const glm::vec2& get_size() const noexcept;

        void set_checked_texture(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_checked_texture() const noexcept;

        void set_unchecked_texture(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_unchecked_texture() const noexcept;

        void set_checked(bool value) noexcept;
        bool get_checked() const noexcept;

        void on_change(const std::function<void (bool)>& cb) noexcept;

    private:
        bool checked = false;
        std::shared_ptr<Texture> unchecked_texture;
        std::shared_ptr<Texture> checked_texture;

        std::shared_ptr<Rectangle> background;
        std::shared_ptr<HitArea>   hit_area;

        std::function<void (bool)> change_cb;

        void handle_click();
    };
}

#endif
