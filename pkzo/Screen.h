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

#include <glm/glm.hpp>

#include "Scene.h"

namespace pkzo
{
    class OrthographicCamera;

    //! Screen
    class PKZO_EXPORT Screen : public Scene
    {
    public:
        //! Create screen
        //!
        //! @param size the size of the screen
        Screen(const glm::vec2& size);
        ~Screen();

        //! Get the Screen size.
        const glm::vec2& get_size() const noexcept;

        //! Draw screen
        void draw() const noexcept;

    private:
        glm::vec2 size;
        std::shared_ptr<OrthographicCamera> camera;
    };

    PKZO_EXPORT
    glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos);
}
