// OpenGL Object Wrapper
// Copyright 2016-2023 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include <string>
#include <source_location>

#include <GL/glew.h>

#include "defines.h"

namespace glow
{
    //! Initialize the openGL context.
    //!
    //! @note This function does not create the OpenGL context,
    //! it applies the nessesary environment, like loading GLEW and
    //! clearing errors.
    GLOW_EXPORT void init();

    //! Clear any pending openGL errors.
    GLOW_EXPORT void clear_erorrs() noexcept;

    //! Translate an openGL error code to a string.
    //!
    //! @param error the error code
    //! @return the error string
    GLOW_EXPORT std::string get_error_string(GLenum error) noexcept;

    //! Check for openGL errors.
    GLOW_EXPORT void check_error(const std::source_location& location = std::source_location::current());

    class GLOW_EXPORT Section
    {
    public:
        explicit Section(const std::string_view id);
        ~Section();

    private:
        Section(const Section&) = delete;
        Section& operator = (const Section&) = delete;
    };
}

#ifndef NDEBUG
#define GLOW_CHECK_ERROR() glow::check_error()
#else
#define GLOW_CHECK_ERROR()
#endif

#include "Shader.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "Pipeline.h"
