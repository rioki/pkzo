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

#include "OpenGLFrameBuffer.h"

#include "debug.h"

namespace pkzo
{
    GLenum buffers[] = { GL_COLOR_ATTACHMENT0,
                         GL_COLOR_ATTACHMENT1,
                         GL_COLOR_ATTACHMENT2,
                         GL_COLOR_ATTACHMENT3,
                         GL_COLOR_ATTACHMENT4,
                         GL_COLOR_ATTACHMENT5,
                         GL_COLOR_ATTACHMENT6,
                         GL_COLOR_ATTACHMENT7,
                         GL_COLOR_ATTACHMENT8,
                         GL_COLOR_ATTACHMENT9,
                         GL_COLOR_ATTACHMENT10,
                         GL_COLOR_ATTACHMENT11,
                         GL_COLOR_ATTACHMENT12,
                         GL_COLOR_ATTACHMENT13,
                         GL_COLOR_ATTACHMENT14,
                         GL_COLOR_ATTACHMENT15};

    std::string get_color_id(unsigned int i)
    {
        check(i < 16u);
        switch (i)
        {
            case  0: return "[Color0]";
            case  1: return "[Color1]";
            case  2: return "[Color2]";
            case  3: return "[Color3]";
            case  4: return "[Color4]";
            case  5: return "[Color5]";
            case  6: return "[Color6]";
            case  7: return "[Color7]";
            case  8: return "[Color8]";
            case  9: return "[Color9]";
            case 10: return "[Color10]";
            case 11: return "[Color11]";
            case 12: return "[Color12]";
            case 13: return "[Color13]";
            case 14: return "[Color14]";
            case 15: return "[Color15]";
            default: std::unreachable();
        }
    }

    std::shared_ptr<OpenGLFrameBuffer> OpenGLFrameBuffer::create(const BufferConfig& config)
    {
        auto buffer = std::make_shared<OpenGLFrameBuffer>();
        buffer->bind();

        if (config.depth)
        {
            buffer->attach_depth(OpenGLTexture::create({
                .id          = config.id + "[Normal]",
                .size        = config.size,
                .data_type   = *config.depth,
                .color_mode  = ColorMode::DEPTH,
            }));
        }

        for (auto i = 0u; i < config.colors.size(); i++)
        {
            buffer->attach_color(i, OpenGLTexture::create({
                .id         = config.id + get_color_id(i),
                .size       = config.size,
                .data_type  = config.colors[i].data,
                .color_mode = config.colors[i].color,
            }));
        }

        if (buffer->check_buffer() == false)
        {
            throw std::runtime_error("Failed to create frame buffer.");
        }

        return buffer;
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer()
    {
        glGenFramebuffers(1, &handle);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &handle);
    }

    glm::uvec2 OpenGLFrameBuffer::get_size() const
    {
        if (color_attachement.size() > 0)
        {
            return color_attachement[0]->get_size();
        }

        if (depth_attachment)
        {
            return depth_attachment->get_size();
        }

        return {0u, 0u};
    }

    std::shared_ptr<Texture> OpenGLFrameBuffer::get_depth() const
    {
        return depth_attachment;
    }

    std::vector<std::shared_ptr<Texture>> OpenGLFrameBuffer::get_colors() const
    {
        return {begin(color_attachement), end(color_attachement)};
    }

    std::shared_ptr<Texture> OpenGLFrameBuffer::get_color(unsigned int slot) const
    {
        if (slot < color_attachement.size())
        {
            return color_attachement[slot];
        }
        return nullptr;
    }

    void OpenGLFrameBuffer::attach_depth(const std::shared_ptr<OpenGLTexture>& texture)
    {
        check(texture != nullptr);

        if (texture != nullptr)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->get_handle(), 0);
        }
        else
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
        }
        depth_attachment = texture;
    }

    void OpenGLFrameBuffer::attach_color(unsigned int slot, const std::shared_ptr<OpenGLTexture>& texture, unsigned int level)
    {
        check(slot < 16);
        check(texture != nullptr);

        if (slot >= color_attachement.size())
        {
            color_attachement.resize(slot + 1);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, texture->get_handle(), level);

        // Assumption: we are assuming frame buffers are not sparse.
        glNamedFramebufferDrawBuffers(handle, slot + 1, buffers);

        color_attachement[slot] = texture;
    }

    void OpenGLFrameBuffer::attach_color(unsigned int slot, const std::shared_ptr<OpenGLCubeMap>& texture, CubeFace face, unsigned int level)
    {
        check(slot < 16);
        check(texture != nullptr);

        if (slot >= color_attachement.size())
        {
            color_attachement.resize(slot + 1);
        }

        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(face);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, target, texture->get_handle(), level);

        // Assumption: we are assuming frame buffers are not sparse.
        glNamedFramebufferDrawBuffers(handle, slot + 1, buffers);
    }

    bool OpenGLFrameBuffer::check_buffer() const
    {
        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        return status == GL_FRAMEBUFFER_COMPLETE;
    }

    void OpenGLFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, handle);
    }
}
