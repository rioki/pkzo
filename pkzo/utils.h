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

#include <string>
#include <glm/glm.hpp>

namespace pkzo
{
    inline
    glm::vec3 rgb(float r, float g, float b)
    {
        return { r, g, b };
    }

    inline
    glm::vec3 rgb(uint8_t r, uint8_t g, uint8_t b)
    {
        return rgb((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
    }

    inline
    glm::vec3 rgb(uint32_t hex)
    {
        uint8_t r = (hex & 0x00FF0000) >> 16;
        uint8_t g = (hex & 0x0000FF00) >> 8;
        uint8_t b = (hex & 0x000000FF) >> 0;
        return rgb(r, g, b);
    }

    inline
    glm::vec4 rgba(float r, float g, float b, float a)
    {
        return { r, g, b, a };
    }

    inline
    glm::vec4 rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return rgba((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
    }

    inline
    glm::vec4 rgba(uint32_t hex)
    {
        uint8_t r = (hex & 0xFF000000) >> 24;
        uint8_t g = (hex & 0x00FF0000) >> 16;
        uint8_t b = (hex & 0x0000FF00) >> 8;
        uint8_t a = (hex & 0x000000FF) >> 0;
        return rgba(r, g, b, a);
    }

    constexpr unsigned int hash(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
    }

    inline unsigned int hash(const std::string& str)
    {
        return hash(str.c_str());
    }
}
