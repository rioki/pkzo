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
#include <glm/gtc/matrix_transform.hpp>

#ifdef _WIN32
#include <windows.h>
#undef max
#undef min
#endif

#include "compose.h"

namespace pkzo
{
    // inline compose's to_string and from_string
    using impl::to_string;
    using impl::from_string;

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

    inline glm::mat4 lookat(const glm::vec3 pos, const glm::vec3 target, const glm::vec3 up)
    {
        return glm::inverse(glm::lookAt(pos, target, up));
    }

    inline glm::mat4 position(float x, float y)
    {
        return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    }

    inline glm::mat4 position(const glm::vec2& pos)
    {
        return position(pos.x, pos.y);
    }

    inline glm::mat4 position(float x, float y, float z)
    {
        return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    }

    inline glm::mat4 position(const glm::vec3 pos)
    {
        return position(pos.x, pos.y, pos.z);
    }

    constexpr unsigned int hash(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
    }

    inline unsigned int hash(const std::string& str)
    {
        return hash(str.c_str());
    }

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    PKZO_EXPORT std::u32string utf32(const std::string& buff);

    PKZO_EXPORT const char* gl_error_to_string(unsigned int glerror);

#ifndef NDEBUG
    PKZO_EXPORT void handle_gl_error(const std::string_view func, const std::string_view descr);
#endif

#ifdef _WIN32
    PKZO_EXPORT std::string LoadTextResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType);
#endif
}

#ifndef NDEBUG
#define DBG_CHECK_GLERROR(DESCR) ::pkzo::handle_gl_error(__FUNCTION__, DESCR)
#else
#define DBG_CHECK_GLERROR(DESCR)
#endif