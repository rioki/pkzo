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

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include <pkzo/pkzo.h>

#include "SceneNodeGroup.h"
#include "Button.h"

namespace pkzo
{
    class PKZO_EXPORT Menu : public SceneNodeGroup
    {
    public:
        Menu(const std::shared_ptr<pkzo::Texture>& top_texture, const std::shared_ptr<pkzo::Texture>& body_texture, const std::shared_ptr<pkzo::Texture>& bottom_texture, const std::shared_ptr<Font>& caption_font, const glm::vec4& text_color, const std::vector<std::string>& options) noexcept;
        ~Menu();

        glm::vec2 get_size() const noexcept;

        void on_select(const std::function<void (size_t)>& cb);

    private:
        std::shared_ptr<Rectangle>           top;
        std::vector<std::shared_ptr<Button>> bodies;
        std::shared_ptr<Rectangle>           bottom;
        std::function<void (size_t)>         select_cb;
    };
}
