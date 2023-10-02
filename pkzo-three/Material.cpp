// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "Material.h"

namespace pkzo::three
{
    glm::vec3 rgb(unsigned int hex)
    {
        auto r = (hex >> 16) & 0xFF;
        auto g = (hex >> 8) & 0xFF;
        auto b = hex & 0xFF;
        return rgb(r, g, b);
    }

    glm::vec4 rgba(unsigned int hex)
    {
        auto r = (hex >> 24) & 0xFF;
        auto g = (hex >> 16) & 0xFF;
        auto b = (hex >> 8) & 0xFF;
        auto a = hex & 0xFF;
        return rgba(r, g, b, a);
    }

    glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b)
    {
        return rgb(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    {
        return rgba(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    glm::vec3 rgb(float r, float g, float b)
    {
        return glm::vec3(r, g, b);
    }

    glm::vec4 rgba(float r, float g, float b, float a)
    {
        return glm::vec4(r, g, b, a);
    }
}
