// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "color.h"

namespace pkzo
{
    glm::vec4 rgba(unsigned int hex) noexcept
    {
        return glm::vec4(
            static_cast<float>((hex >> 24) & 0xFF) / 255.0f,
            static_cast<float>((hex >> 16) & 0xFF) / 255.0f,
            static_cast<float>((hex >>  8) & 0xFF) / 255.0f,
            static_cast<float>((hex >>  0) & 0xFF) / 255.0f
        );
    }

    glm::vec4 rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept
    {
        return glm::vec4(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f);
    }

    glm::vec4 rgba(float r, float g, float b, float a) noexcept
    {
        return glm::vec4(r, g, b, a);
    }

    glm::vec3 rgb(unsigned int hex) noexcept
    {
        return glm::vec3(
            static_cast<float>((hex >> 16) & 0xFF) / 255.0f,
            static_cast<float>((hex >>  8) & 0xFF) / 255.0f,
            static_cast<float>((hex >>  0) & 0xFF) / 255.0f
        );
    }

    glm::vec3 rgb(unsigned char r, unsigned char g, unsigned char b) noexcept
    {
        return glm::vec3(static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f);
    }

    glm::vec3 rgb(float r, float g, float b) noexcept
    {
        return glm::vec3(r, g, b);
    }
}
