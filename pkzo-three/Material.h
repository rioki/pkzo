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

#pragma once
#include <pkzo/config.h>

#include <glm/glm.hpp>

namespace pkzo::three
{
    //! @brief Convert RGB color from hexadecimal to glm::vec3.
    //!
    //! @param hex The RGB color in hexadecimal format (e.g., 0xFF0000 for red).
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(unsigned int hex);

    //! @brief Convert RGBA color from hexadecimal to glm::vec4.
    //!
    //! @param hex The RGBA color in hexadecimal format (e.g., 0xFF0000FF for red, fully opaque).
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(unsigned int hex);

    //! @brief Convert RGB color from separate 0-255 components to glm::vec3.
    //!
    //! @param r Red component, in [0, 255].
    //! @param g Green component, in [0, 255].
    //! @param b Blue component, in [0, 255].
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b);

    //! @brief Convert RGBA color from separate 0-255 components to glm::vec4.
    //!
    //! @param r Red component, in [0, 255].
    //! @param g Green component, in [0, 255].
    //! @param b Blue component, in [0, 255].
    //! @param a Alpha component, in [0, 255].
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

    //! @brief Convert RGB color from separate float components to glm::vec3.
    //!
    //! @param r Red component, in [0.0, 1.0].
    //! @param g Green component, in [0.0, 1.0].
    //! @param b Blue component, in [0.0, 1.0].
    //! @return The color as a glm::vec3, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec3 rgb(float r, float g, float b);

    //! @brief Convert RGBA color from separate float components to glm::vec4.
    //!
    //! @param r Red component, in [0.0, 1.0].
    //! @param g Green component, in [0.0, 1.0].
    //! @param b Blue component, in [0.0, 1.0].
    //! @param a Alpha component, in [0.0, 1.0].
    //! @return The color as a glm::vec4, with each channel in [0.0, 1.0].
    PKZO_EXPORT glm::vec4 rgba(float r, float g, float b, float a);
}
