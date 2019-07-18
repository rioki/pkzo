// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_FRAME_BUFFER_H_
#define _PKZO_FRAME_BUFFER_H_

#include "defines.h"

#include <list>
#include <array>
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "stdex.h"
#include "ColorMode.h"

namespace pkzo
{
    class Shader;
    class Texture;

    struct BufferConfig
    {
        std::string input_name;
        std::string output_name;
        ColorMode type;
    };

    /*!
     * OpenGL Frame Buffer
     */
    class PKZO_EXPORT FrameBuffer : private stdex::non_copyable
    {
    public:
        /*!
         * Construct a frame default buffer with a color and depth atachment.
         */
        FrameBuffer(glm::uvec2 size);

        /*!
         * Create a frame buffer after a specific schema.
         */
        FrameBuffer(glm::uvec2 size, std::list<BufferConfig> config);

        ~FrameBuffer();

        /*!
         * Resize the framebuffer
         */
        void resize(glm::uvec2 value);

        /*!
         * Get the current frame buffer.
         */
        glm::uvec2 get_size();

        /*!
         * Bind the framebuffer as output.
         */
        void bind(Shader& shader);

        void bind();

        /*!
         * Unbind outputs.
         */
        void unbind();

        /*!
         * Bind framebufer textures as inputs.
         */
        void bind_inputs(Shader& shader);

    private:
        struct Attachment
        {
            glm::uint id;
            glm::uint index;
            std::string input_name;
            std::string output_name;
            std::shared_ptr<Texture> texture;
        };

        glm::uvec2 size;
        glm::uint  glid = 0;
        std::shared_ptr<Attachment> depth_attachment;
        std::vector<std::shared_ptr<Attachment>> color_attachments;
    };

    class GeometryBuffer : public FrameBuffer
    {
    public:
        GeometryBuffer(glm::uvec2 s);
    };
}

#endif
