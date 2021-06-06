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

#include <memory>
#include <pkzo/SceneNodeGroup.h>
#include <pkzo/Font.h>
#include <pkzo/Material.h>
#include <pkzo/Text.h>
#include <pkzo/HitArea.h>

namespace pong2d
{
    class KeyInput : public pkzo::SceneNodeGroup
    {
    public:
        KeyInput(pkzo::Key key, const std::shared_ptr<pkzo::Font>& font, const std::shared_ptr<pkzo::Material>& material) noexcept;

        void set_key(pkzo::Key value) noexcept;
        pkzo::Key get_key() const noexcept;

        rsig::signal<>& get_click_signal() noexcept;
        rsig::connection on_click(const std::function<void ()>& cb) noexcept;

    private:
        pkzo::Key key;
        std::shared_ptr<pkzo::Text>    text;
        std::shared_ptr<pkzo::HitArea> hit_area;

        rsig::signal<>                 click_signal;
    };
}
