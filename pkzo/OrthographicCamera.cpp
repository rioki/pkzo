//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "OrthographicCamera.h"

namespace pkzo
{
    OrthographicCamera::OrthographicCamera(const glm::vec2& s) noexcept
    {
        set_resolution(s);
        size = glm::vec3(s, 1.0f);
    }

    const glm::vec3& OrthographicCamera::get_size() const noexcept
    {
        return size;
    }

    void OrthographicCamera::set_size(const glm::vec3& value)
    {
        size = value;
    }

    glm::mat4 OrthographicCamera::get_projection() const noexcept
    {
        auto hs = size * 0.5f;
        return glm::ortho(-hs.x, hs.x, -hs.y, hs.y, -hs.z, hs.z);
    }
}
