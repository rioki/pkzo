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

#include "GraphicContext.h"

namespace pkzo
{
    class OpenGLShader;
    class OpenGLTexture;
    class OpenGLMesh;
    class OpenGLFrameBuffer;
    class OpenGLDebugRenderer;

    class PKZO_EXPORT OpenGLGraphicContext : public GraphicContext
    {
    public:
        OpenGLGraphicContext(SDL_Window* window);
        ~OpenGLGraphicContext();

        Api get_api() const override;

        std::shared_ptr<MemoryTexture> screenshot() const override;

        std::shared_ptr<Shader> compile(const Shader::Source& source) override;
        std::shared_ptr<FrameBuffer> create_frame_buffer(const FrameBuffer::BufferConfig& config) override;

        std::shared_ptr<CubeMap> generate_cubemap(const CubeMapGenerator& generator) override;

        std::shared_ptr<Mesh> upload_mesh(MeshData data, bool stream = false) override;

        void set_viewport(const Viewport& viewport) override;
        Viewport get_viewport() const override;

        void clear_screen() override;

        void start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader) override;
        void start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<FrameBuffer>& frame_buffer) override;

        void set_blend_mode(BlendMode mode) override;
        void set_depth_test(DepthTest mode) override;

        void set_uniform(int loc, int value) override;
        void set_uniform(int loc, float value) override;
        void set_uniform(int loc, const glm::ivec2& value) override;
        void set_uniform(int loc, const glm::ivec3& value) override;
        void set_uniform(int loc, const glm::ivec4& value) override;
        void set_uniform(int loc, const glm::vec2& value) override;
        void set_uniform(int loc, const glm::vec3& value) override;
        void set_uniform(int loc, const glm::vec4& value) override;
        void set_uniform(int loc, const glm::mat2& value) override;
        void set_uniform(int loc, const glm::mat3& value) override;
        void set_uniform(int loc, const glm::mat4& value) override;
        void set_uniform(int loc, const UniformValue& value) override;

        void bind_texture(int slot, const std::shared_ptr<Texture>& texture, FallbackTexture fallback = FallbackTexture::WHITE) override;
        void bind_texture(int slot, const std::shared_ptr<CubeMap>& texture) override;

        void draw(const std::shared_ptr<Mesh>& mesh) override;
        void draw_fullscreen() override;

        void end_pass() override;

        void swap_buffers() override;

    private:
        SDL_Window*   window    = nullptr;
        SDL_GLContext glcontext = nullptr;

        std::weak_ptr<OpenGLDebugRenderer> weak_debug_renderer;

        std::shared_ptr<OpenGLShader>      current_shader;
        std::shared_ptr<OpenGLFrameBuffer> current_frame_buffer;

        std::map<std::weak_ptr<Texture>, std::shared_ptr<OpenGLTexture>, std::owner_less<>> texture_cache;
        std::map<std::weak_ptr<Mesh>, std::shared_ptr<OpenGLMesh>, std::owner_less<>>       mesh_cache;

        std::shared_ptr<OpenGLTexture> white_fallback_texture;
        std::shared_ptr<OpenGLTexture> normal_fallback_texture;

        std::shared_ptr<OpenGLMesh> fullscreen_mesh;

        std::shared_ptr<OpenGLTexture> upload(const std::shared_ptr<Texture>& texture);
        std::shared_ptr<OpenGLMesh> upload(const std::shared_ptr<Mesh>& mesh);
        void collect_garbage();
    };
}

