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

#include <map>
#include <memory>
#include <variant>

#include <glm/glm.hpp>
#include <SDL3/SDL.h>

#include "api.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FrameBuffer.h"
#include "CubeMap.h"

namespace pkzo
{
    class MemoryTexture;

    enum class Api : Uint64
    {
        OPENGL = SDL_WINDOW_OPENGL,
        // VULKAN
    };

    struct Viewport
    {
        glm::uvec2 position = glm::uvec2(0u);
        glm::uvec2 size     = glm::uvec2(0u);
    };

    enum class BlendMode
    {
        DISABLED,
        ALPHA,
        ONE
    };

    enum class DepthTest
    {
        DISABLED,
        READ,
        ENABLED
    };

    using UniformValue = std::variant<int, float,
                                      glm::ivec2, glm::ivec3, glm::ivec4,
                                      glm::vec2, glm::vec3, glm::vec4,
                                      glm::mat2, glm::mat3, glm::mat4>;

    enum class GeneratorUniformLocation {
        MIPLEVEL,
        TEXTURE,
        CUBEMAP,
        CUBEMAP_TBN
    };

    using TextureOrCubeMap = std::variant<std::shared_ptr<Texture>, std::shared_ptr<CubeMap>>;

    struct CubeMapGenerator
    {
        std::string                     id         = "Generated Cubemap";
        unsigned int                    size       = 1024u;
        DataType                        data_type  = DataType::UNSIGNED_BYTE;
        ColorMode                       color_mode = ColorMode::RGB;
        std::shared_ptr<Shader>         shader;
        std::map<int, UniformValue>     uniforms;
        std::map<int, TextureOrCubeMap> textures;
        unsigned int                    miplevels  = 1u;
        std::shared_ptr<CubeMap>        target;
    };

    enum class FallbackTexture
    {
        WHITE,
        NORMAL
    };

    class PKZO_EXPORT GraphicContext
    {
    public:
        static std::unique_ptr<GraphicContext> create(Api api, SDL_Window* window);

        virtual ~GraphicContext() = default;

        //! Get the API fo the Graphic context.
        [[nodiscard]]
        virtual Api get_api() const = 0;

        virtual std::shared_ptr<MemoryTexture> screenshot() const = 0;

        virtual std::shared_ptr<Shader> compile(const Shader::Source& source) = 0;

        virtual std::shared_ptr<FrameBuffer> create_frame_buffer(const FrameBuffer::BufferConfig& config) = 0;

        virtual std::shared_ptr<CubeMap> generate_cubemap(const CubeMapGenerator& generator) = 0;

        virtual std::shared_ptr<Mesh> upload_mesh(MeshData data, bool stream = false) = 0;

        virtual void set_viewport(const Viewport& viewport) = 0;
        virtual Viewport get_viewport() const = 0;

        virtual void clear_screen() = 0;

        virtual void start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader) = 0;
        virtual void start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<FrameBuffer>& frame_buffer) = 0;
        virtual void set_blend_mode(BlendMode mode) = 0;
        virtual void set_depth_test(DepthTest mode) = 0;

        virtual void set_uniform(int loc, int value) = 0;
        virtual void set_uniform(int loc, float value) = 0;
        virtual void set_uniform(int loc, const glm::ivec2& value) = 0;
        virtual void set_uniform(int loc, const glm::ivec3& value) = 0;
        virtual void set_uniform(int loc, const glm::ivec4& value) = 0;
        virtual void set_uniform(int loc, const glm::vec2& value) = 0;
        virtual void set_uniform(int loc, const glm::vec3& value) = 0;
        virtual void set_uniform(int loc, const glm::vec4& value) = 0;
        virtual void set_uniform(int loc, const glm::mat2& value) = 0;
        virtual void set_uniform(int loc, const glm::mat3& value) = 0;
        virtual void set_uniform(int loc, const glm::mat4& value) = 0;
        virtual void set_uniform(int loc, const UniformValue& value) = 0;

        virtual void bind_texture(int slot, const std::shared_ptr<Texture>& texture, FallbackTexture fallback = FallbackTexture::WHITE) = 0;
        virtual void bind_texture(int slot, const std::shared_ptr<CubeMap>& texture) = 0;

        virtual void draw(const std::shared_ptr<Mesh>& mesh) = 0;
        virtual void draw_fullscreen() = 0;

        virtual void end_pass() = 0;

        virtual void swap_buffers() = 0;

    };
}
