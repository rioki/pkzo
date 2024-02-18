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

#include "pch.h"
#include "glow.h"
#include "FrameBuffer.h"

namespace glow
{
    const auto default_config = std::vector<BufferConfig>{
        {"uColor", "oFragColor", ColorMode::RGBA,  DataType::UINT8},
        {"uDepth", "oFragDepth", ColorMode::DEPTH, DataType::UINT16}
    };

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

    FrameBuffer::FrameBuffer(glm::uvec2 size)
    : FrameBuffer(size, default_config) {}

    FrameBuffer::FrameBuffer(glm::uvec2 size, std::vector<BufferConfig> config)
    : size(size)
    {
        auto color_count = 0;
        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        for (auto& c : config)
        {
            auto attachment = c.mode == ColorMode::DEPTH ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0 + color_count;

            auto texture = std::make_shared<Texture>();
            texture->upload(size, c.mode, c.type);

            attachments.emplace_back(attachment, c.input_name, c.output_name, c.mode, c.type, texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->get_id(), 0);

            if (c.mode != ColorMode::DEPTH)
            {
                color_count++;
            }
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw std::runtime_error("Could not create frame buffer.");
        }

        glDrawBuffers(color_count, buffers);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLOW_CHECK_ERROR();
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &id);
        GLOW_CHECK_ERROR();
    }

    glm::uvec2 FrameBuffer::get_size() const noexcept
    {
        return size;
    }

    void FrameBuffer::resize(glm::uvec2 value)
    {
        size = value;

        for (auto& a : attachments)
        {
            a.texture->upload(size, a.mode, a.type);
        }
    }

    void FrameBuffer::bind(Shader& shader) const noexcept
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        for (auto& a : attachments)
        {
            if (a.id != GL_DEPTH_ATTACHMENT)
            {
                shader.bind_output(a.output_name, a.id - GL_COLOR_ATTACHMENT0);
            }
        }

        GLOW_CHECK_ERROR();
    }

    void FrameBuffer::bind() const noexcept
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        GLOW_CHECK_ERROR();
    }

    void FrameBuffer::clear() const noexcept
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLOW_CHECK_ERROR();
    }

    std::shared_ptr<Parameters> FrameBuffer::get_input_parameters() const noexcept
    {
        auto parameters = std::make_shared<Parameters>();

        parameters->set_value("uFrameBufferSize", size);

        for (auto& a : attachments)
        {
            parameters->set_value(a.input_name, a.texture);
        }

        return parameters;
    }
}
