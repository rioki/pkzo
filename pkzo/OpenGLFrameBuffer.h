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

#include "FrameBuffer.h"

#include <GL/glew.h>

#include "OpenGLTexture.h"
#include "OpenGLCubeMap.h"

namespace pkzo
{
    class PKZO_EXPORT OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        static std::shared_ptr<OpenGLFrameBuffer> create(const BufferConfig& config);

        OpenGLFrameBuffer();
        ~OpenGLFrameBuffer();

        glm::uvec2 get_size() const override;

        std::shared_ptr<Texture> get_depth() const override;

        std::vector<std::shared_ptr<Texture>> get_colors() const override;
        std::shared_ptr<Texture> get_color(unsigned int slot) const override;

        void attach_depth(const std::shared_ptr<OpenGLTexture>& texture);
        void attach_color(unsigned int slot, const std::shared_ptr<OpenGLTexture>& texture, unsigned int level = 0);
        void attach_color(unsigned int slot, const std::shared_ptr<OpenGLCubeMap>& texture, CubeFace face, unsigned int level = 0);
        bool check_buffer() const;
        void bind();

    private:
        glm::uint handle = 0u;

        std::shared_ptr<OpenGLTexture>              depth_attachment;
        std::vector<std::shared_ptr<OpenGLTexture>> color_attachement;

    };
}
