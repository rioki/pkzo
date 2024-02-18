// OpenGL Object Wrapper
// Copyright 2016-2022 Sean Farrell <sean.farrell@rioki.org>
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

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "defines.h"
#include "Texture.h"
#include "Shader.h"
#include "Parameters.h"

namespace glow
{
    struct BufferConfig
    {
        std::string input_name;
        std::string output_name;
        ColorMode   mode;
        DataType    type;
    };

    //! OpenGL Frame Buffer
    class GLOW_EXPORT FrameBuffer
    {
    public:
        //! Create standard frame buffer with color and depth buffer
        //!
        //! @param size the size of the frame buffer
        FrameBuffer(glm::uvec2 size);

        //! Create frame buffer with custom configuration
        //!
        //! @param size the size of the frame buffer
        //! @param config the configuration of the frame buffer
        FrameBuffer(glm::uvec2 size, std::vector<BufferConfig> config);

        ~FrameBuffer();

        //! Get the size of the frame buffer
        glm::uvec2 get_size() const noexcept;

        //! Resize the frame buffer
        void resize(glm::uvec2 value);

        //! Bind the frame buffer and adjust the attachment
        void bind(Shader& shader) const noexcept;

        //! Clear the frame buffer
        void clear() const noexcept;

        //! Bind the frame buffer
        //!
        //! @note The attachments in the shader must match the buffer config using the location attribute.
        void bind() const noexcept;

        //! Get the textrures as input parameters for the next stages
        std::shared_ptr<Parameters> get_input_parameters() const noexcept;

    private:
        struct Attachment
        {
            glm::uint                id;
            std::string              input_name;
            std::string              output_name;
            ColorMode                mode;
            DataType                 type;
            std::shared_ptr<Texture> texture;
        };

        glm::uvec2              size;
        unsigned int            id = 0;
        std::vector<Attachment> attachments;

        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer& operator = (const FrameBuffer& other) = delete;
    };
}
