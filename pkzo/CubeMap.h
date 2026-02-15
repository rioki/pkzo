// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <filesystem>

#include <glm/glm.hpp>

#include "api.h"
#include "Texture.h"

namespace pkzo
{
    enum class CubeFace : int
    {
        XPOS,
        XNEG,
        YPOS,
        YNEG,
        ZPOS,
        ZNEG
    };

    class PKZO_EXPORT CubeMap
    {
    public:
        struct CreateSpecs
        {
            std::string  id         = "unnamed";
            unsigned int size       = 1024u;
            DataType     data_type  = DataType::UNSIGNED_BYTE;
            ColorMode    color_mode = ColorMode::RGB;
            unsigned int miplevels  = 1u;
        };

        CubeMap() = default;
        virtual ~CubeMap() = default;

        virtual std::string get_id() const = 0;
        virtual unsigned int get_size() const = 0;
        virtual DataType get_data_type() const = 0;
        virtual ColorMode get_color_mode() const = 0;

    private:
        CubeMap(const CubeMap&) = delete;
        CubeMap& operator = (const CubeMap&) = delete;
    };
}
