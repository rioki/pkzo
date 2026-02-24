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
    class PKZO_EXPORT FrameBuffer
    {
    public:
        struct ColorConfig
        {
            DataType  data;
            ColorMode color;
        };

        struct BufferConfig
        {
            std::string                       id     = "Unnamed Frame Buffer";
            glm::uvec2                        size   = glm::uvec2(512);
            std::optional<DataType>           depth  = DataType::FLOAT;
            std::vector<ColorConfig>          colors = {{DataType::FLOAT, ColorMode::RGBA}};
        };

        FrameBuffer() = default;
        virtual ~FrameBuffer() = default;

        virtual glm::uvec2 get_size() const = 0;

        virtual std::shared_ptr<Texture> get_depth() const = 0;

        virtual std::vector<std::shared_ptr<Texture>> get_colors() const = 0;
        virtual std::shared_ptr<Texture> get_color(unsigned int slot) const = 0;

    private:
        FrameBuffer(const FrameBuffer&) = delete;
        FrameBuffer& operator = (const FrameBuffer&) = delete;
    };
}
