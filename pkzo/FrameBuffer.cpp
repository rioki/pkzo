// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "FrameBuffer.h"

#include <gl/glew.h>

#include "dbg.h"
#include "Texture.h"
#include "Shader.h"

namespace pkzo
{
    const auto default_config = std::list<BufferConfig>{
        {"pkzo_Color", "pkzo_FragColor", ColorMode::RGBA},
        {"pkzo_Depth", "pkzo_FragDepth", ColorMode::DEPTH}};

    const auto gbuffer_config = std::list<BufferConfig>{
        {"pkzo_Depth",    "pkzo_FragDepth",    ColorMode::DEPTH},
        {"pkzo_Position", "pkzo_FragPosition", ColorMode::RGBA_FLOAT}, // TODO remove me
        {"pkzo_Normal",   "pkzo_FragNormal",   ColorMode::RGBA_FLOAT},
        {"pkzo_Albedo",   "pkzo_FragAlbedo",   ColorMode::RGBA_FLOAT},
        {"pkzo_RMHAO",    "pkzo_FragRMHAO",    ColorMode::RGBA_FLOAT}};

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

    FrameBuffer::FrameBuffer(glm::uvec2 s)
    : FrameBuffer(s, default_config) {}

    FrameBuffer::FrameBuffer(glm::uvec2 s, std::list<BufferConfig> config)
    : size(s)
    {
        glGenFramebuffers(1, &glid);
        PKZO_CHECK_OPENGL(glGetError());

        glBindFramebuffer(GL_FRAMEBUFFER, glid);
        glm::uint next_attachment = 0;
        for (auto c : config)
        {
            if (c.type == ColorMode::DEPTH)
            {
                if (!depth_attachment)
                {
                    depth_attachment = std::make_shared<Attachment>(Attachment{
                        GL_DEPTH_ATTACHMENT,
                        0u,
                        c.input_name,
                        c.output_name,
                        std::make_shared<Texture>(size, c.type)
                    });
                    glFramebufferTexture2D(GL_FRAMEBUFFER, depth_attachment->id, GL_TEXTURE_2D, depth_attachment->texture->get_handle(), 0);
                    PKZO_CHECK_OPENGL(glGetError());
                }
                else
                {
                    PKZO_THROW(std::logic_error, "Only one depth attachment can be bound on a frame buffer.");
                }
            }
            else
            {
                color_attachments.push_back(std::make_shared<Attachment>(Attachment{
                    GL_COLOR_ATTACHMENT0 + next_attachment,
                    next_attachment,
                    c.input_name,
                    c.output_name,
                    std::make_shared<Texture>(size, c.type)
                }));
                glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachments.back()->id, GL_TEXTURE_2D, color_attachments.back()->texture->get_handle(), 0);
                next_attachment++;
            }
        }
        glNamedFramebufferDrawBuffers(glid, next_attachment, buffers);
    }

    FrameBuffer::~FrameBuffer()
    {
        PKZO_ASSERT(glid != 0);
        glDeleteFramebuffers(1, &glid);
        PKZO_CHECK_OPENGL(glGetError());
    }

    void FrameBuffer::resize(glm::uvec2 value)
    {
        if (size == value)
        {
            return;
        }

        if (depth_attachment)
        {
            PKZO_ASSERT(depth_attachment->texture);
            depth_attachment->texture->resize(value);
        }

        for (auto& color_attachment : color_attachments)
        {
            if (color_attachment)
            {
                PKZO_ASSERT(color_attachment->texture);
                color_attachment->texture->resize(value);
            }
        }

        size = value;
    }

    glm::uvec2 FrameBuffer::get_size()
    {
        return size;
    }

    void FrameBuffer::bind(Shader& shader)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, glid);

        for (auto& color_attachment : color_attachments)
        {
            PKZO_ASSERT(color_attachment);
            //shader.bind_output(color_attachment->output_name, color_attachment->index);
            PKZO_CHECK_OPENGL(glGetError());
        }
    }

    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, glid);
        PKZO_CHECK_OPENGL(glGetError());
    }

    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        PKZO_CHECK_OPENGL(glGetError());
    }

    void FrameBuffer::bind_inputs(Shader& shader)
    {
        if (depth_attachment)
        {
            shader.set_texture(depth_attachment->input_name, depth_attachment->texture);
        }

        for (auto& color_attachment : color_attachments)
        {
            if (color_attachment)
            {
                shader.set_texture(color_attachment->input_name, color_attachment->texture);
            }
        }
    }

    GeometryBuffer::GeometryBuffer(glm::uvec2 s)
    : FrameBuffer(s, gbuffer_config) {}
}
