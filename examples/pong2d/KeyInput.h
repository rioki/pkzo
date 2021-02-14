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

#ifndef _PONG2D_KEY_INTPUT_H_
#define _PONG2D_KEY_INTPUT_H_

#include <memory>
#include <pkzo/pkzo.h>
#include <pkzo2d/pkzo2d.h>

namespace pong2d
{
    class KeyInput : public pkzo2d::ScreenNodeGroup
    {
    public:
        KeyInput(const std::shared_ptr<pkzo::Font>& font, pkzo::Key key) noexcept;

        void set_key(pkzo::Key value) noexcept;
        pkzo::Key get_key() const noexcept;

        void on_click(const std::function<void ()>& cb);

    private:
        pkzo::Key key;
        std::shared_ptr<pkzo2d::Text>    text;
        std::shared_ptr<pkzo2d::HitArea> hit_area;
    };
}

#endif
