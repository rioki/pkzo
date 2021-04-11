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

#include "pch.h"
#include "utils.h"

#include <iconv.h>

namespace pkzo
{
    std::u32string utf32(const std::string& buff)
    {
        std::u32string result;

        auto cd = iconv_open("UTF-32LE", "UTF-8");
        DBG_ASSERT(cd);

        char* inbuf        = const_cast<char*>(buff.data());
        size_t inbytesleft = buff.size();

        std::array<char, 512> temp;
        char*  outbuf       = temp.data();
        size_t outbytesleft = temp.size();

        while (inbytesleft > 0u)
        {
            iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
            result.append(reinterpret_cast<char32_t*>(temp.data()), reinterpret_cast<char32_t*>(outbuf));
            outbuf       = temp.data();
            outbytesleft = temp.size();
        }

        int r = iconv_close(cd);
        DBG_ASSERT(r == 0);

        return result;
    }


    const char* gl_error_to_string(unsigned int glerror)
    {
        switch (glerror)
        {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        default:
            DBG_FAIL("Unknown glerror type");
            return "UNKNOWN";
        }
    }

#ifndef NDEBUG
    void handle_gl_error(const std::string_view func, const std::string_view descr)
    {
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::stringstream msg;
            msg << func << ": OpenGL Error: " << gl_error_to_string(error) << " while " << descr << "!";
            dbg::trace(msg.str());
            dbg::show_message_box_with_callstack(msg.str());
        }
    }
#endif
}