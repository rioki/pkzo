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

#include "OpenGLGraphicContext.h"

#include <stdexcept>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <tinyformat.h>

#include "debug.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLMesh.h"
#include "OpenGLFrameBuffer.h"
#include "OpenGLCubeMap.h"

namespace pkzo
{
    std::shared_ptr<OpenGLMesh> create_fullscreen_mesh()
    {
        return OpenGLMesh::create({
            .vertexes = {
                {-1.0f, -1.0f, 0.0f},
                { 1.0f, -1.0f, 0.0f},
                { 1.0f,  1.0f, 0.0f},
                {-1.0f,  1.0f, 0.0f}
            },
            .texcoords = {
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f}
            },
            .faces = {
                {0, 1, 2},
                {2, 3, 0}
            }
        });
    }

    std::string source_to_string(GLenum source)
    {
        switch (source) {
            case GL_DEBUG_SOURCE_API:             return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY:     return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION:     return "Application";
            case GL_DEBUG_SOURCE_OTHER:           return "Other";
            default:                              return "Unknown Source";
        }
    }

    std::string type_to_string(GLenum type)
    {
        switch (type) {
            case GL_DEBUG_TYPE_ERROR:               return "Error";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behavior";
            case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
            case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
            case GL_DEBUG_TYPE_MARKER:              return "Marker";
            case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
            case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
            case GL_DEBUG_TYPE_OTHER:               return "Other";
            default:                                return "Unknown Type";
        }
    }

    std::string severity_to_string(GLenum severity)
    {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:         return "High";
            case GL_DEBUG_SEVERITY_MEDIUM:       return "Medium";
            case GL_DEBUG_SEVERITY_LOW:          return "Low";
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
            default:                             return "Unknown Severity";
        }
    }

    void GLAPIENTRY opengl_trace(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
        {
            trace(tfm::format("OpenGL [%s %s %s]: %s", source_to_string(source), type_to_string(type), severity_to_string(severity), message));
        }
    }

    OpenGLGraphicContext::OpenGLGraphicContext(SDL_Window* window)
    : window(window)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        glcontext = SDL_GL_CreateContext(window);
        if (glcontext == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        glewExperimental = GL_TRUE;
        auto err = glewInit();
        if (GLEW_OK != err)
        {
            throw std::runtime_error((const char*)glewGetErrorString(err));
        }

        white_fallback_texture  = OpenGLTexture::create(glm::vec4(1.0f), "Fallback White");
        normal_fallback_texture = OpenGLTexture::create(glm::vec4(0.5f, 0.5f, 1.0f, 1.0f), "Fallback Normal");
    }

    OpenGLGraphicContext::~OpenGLGraphicContext()
    {
        SDL_GL_DestroyContext(glcontext);
        glcontext = nullptr;
    }

    std::shared_ptr<Shader> OpenGLGraphicContext::compile(const Shader::Source& source)
    {
        // TODO caching
        return std::make_shared<OpenGLShader>(source);
    }

    std::shared_ptr<FrameBuffer> OpenGLGraphicContext::create_frame_buffer(const FrameBuffer::BufferConfig& config)
    {
        return OpenGLFrameBuffer::create(config);
    }

    std::shared_ptr<CubeMap> OpenGLGraphicContext::generate_cubemap(const CubeMapGenerator& generator)
    {
        auto framebuffer = std::make_shared<OpenGLFrameBuffer>();
        auto cubemap     = std::dynamic_pointer_cast<OpenGLCubeMap>(generator.target);
        if (cubemap == nullptr)
        {
            check(generator.target == nullptr, "The cube map passed to the OpenGL generator must be an OpenGL cubemap.");
            cubemap = OpenGLCubeMap::create({
                .id          = generator.id,
                .size        = generator.size,
                .data_type   = generator.data_type,
                .color_mode  = generator.color_mode,
                .miplevels   = generator.miplevels
            });
        }

        glFinish();

        static glm::mat3 cube_tbn[6] = {
            glm::mat3(glm::vec3( 0,  0, -1), glm::vec3( 0,  1,  0), glm::vec3( 1,  0,  0)),
            glm::mat3(glm::vec3( 0,  0,  1), glm::vec3( 0,  1,  0), glm::vec3(-1,  0,  0)),
            glm::mat3(glm::vec3( 1,  0,  0), glm::vec3( 0,  0, -1), glm::vec3( 0,  1,  0)),
            glm::mat3(glm::vec3( 1,  0,  0), glm::vec3( 0,  0,  1), glm::vec3( 0, -1,  0)),
            glm::mat3(glm::vec3( 1,  0,  0), glm::vec3( 0,  1,  0), glm::vec3( 0,  0,  1)),
            glm::mat3(glm::vec3(-1,  0,  0), glm::vec3( 0,  1,  0), glm::vec3( 0,  0, -1))
        };

        auto size = generator.size;

        start_pass("Generate Cubemap", generator.shader, framebuffer);

        for (const auto& [loc, value] : generator.uniforms)
        {
            set_uniform(loc, value);
        }

        for (const auto& [slot, texture] : generator.textures)
        {
            std::visit([&] (auto&& tex) { bind_texture(slot, tex); }, texture);
        }

        for (auto mip = 0u; mip < generator.miplevels; mip++)
        {
            glViewport(0, 0, size, size);
            for (auto face = 0u; face < 6; face++)
            {
                framebuffer->attach_color(0, cubemap, static_cast<CubeFace>(face), mip);

                set_uniform(std::to_underlying(GeneratorUniformLocation::MIPLEVEL),    static_cast<int>(mip));
                set_uniform(std::to_underlying(GeneratorUniformLocation::CUBEMAP_TBN), cube_tbn[face]);

                draw_fullscreen();
            }
            size = size / 2u;
        }
        end_pass();

        return cubemap;
    }

    std::shared_ptr<Mesh> OpenGLGraphicContext::upload_mesh(MeshData data, bool stream)
    {
        return OpenGLMesh::create(std::move(data), stream ? OpenGLBuffer::Usage::STREAM : OpenGLBuffer::Usage::STATIC);
    }

    void OpenGLGraphicContext::set_viewport(const Viewport& viewport)
    {
        glViewport(viewport.position.x, viewport.position.y, viewport.size.x, viewport.size.y);
    }

    Viewport OpenGLGraphicContext::get_viewport() const
    {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);
        return {
            .position = {data[0], data[1]},
            .size     = {data[2], data[3]}
        };
    }

    void OpenGLGraphicContext::clear_screen()
    {
        glClearColor(0, 0, 0, 1);
        glClearDepth(1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLGraphicContext::start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader)
    {
        start_pass(name, shader, nullptr);
    }

    void OpenGLGraphicContext::start_pass(const std::string_view name, const std::shared_ptr<Shader>& shader, const std::shared_ptr<FrameBuffer>& frame_buffer)
    {
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, static_cast<GLsizei>(name.size()), name.data());

        current_shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
        check(current_shader);
        current_shader->bind();

        if (frame_buffer)
        {
            current_frame_buffer = std::dynamic_pointer_cast<OpenGLFrameBuffer>(frame_buffer);
            check(current_frame_buffer);
            current_frame_buffer->bind();
        }
        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }

    void OpenGLGraphicContext::set_blend_mode(BlendMode mode)
    {
        switch (mode)
        {
            case BlendMode::DISABLED:
                glDisable(GL_BLEND);
                break;
            case BlendMode::ALPHA:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case BlendMode::ONE:
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);
                break;
            default:
                std::unreachable();
                break;
        }
    }

    void OpenGLGraphicContext::set_depth_test(DepthTest mode)
    {
        switch (mode)
        {
            case DepthTest::DISABLED:
                glDisable(GL_DEPTH_TEST);
                break;
            case DepthTest::READ:
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LEQUAL);
                glDepthMask(GL_FALSE);
                break;
            case DepthTest::ENABLED:
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LEQUAL);
                glDepthMask(GL_TRUE);
                break;
            default:
                std::unreachable();
                break;
        }
    }

    void OpenGLGraphicContext::set_uniform(int loc, int value)
    {
        check(loc >= 0);
        glUniform1i(loc, value);
    }

    void OpenGLGraphicContext::set_uniform(int loc, float value)
    {
        check(loc >= 0);
        glUniform1f(loc, value);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::ivec2& value)
    {
        check(loc >= 0);
        glUniform2i(loc, value.x, value.y);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::ivec3& value)
    {
        check(loc >= 0);
        glUniform3i(loc, value.x, value.y, value.z);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::ivec4& value)
    {
        check(loc >= 0);
        glUniform4i(loc, value.x, value.y, value.z, value.w);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::vec2& value)
    {
        check(loc >= 0);
        glUniform2f(loc, value.x, value.y);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::vec3& value)
    {
        check(loc >= 0);
        glUniform3f(loc, value.x, value.y, value.z);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::vec4& value)
    {
        check(loc >= 0);
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::mat2& value)
    {
        check(loc >= 0);
        glUniformMatrix2fv(loc, 1u, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::mat3& value)
    {
        check(loc >= 0);
        glUniformMatrix3fv(loc, 1u, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLGraphicContext::set_uniform(int loc, const glm::mat4& value)
    {
        check(loc >= 0);
        glUniformMatrix4fv(loc, 1u, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLGraphicContext::set_uniform(int loc, const UniformValue& value)
    {
        std::visit([&](auto&& val){ set_uniform(loc, val); }, value);
    }

    void OpenGLGraphicContext::bind_texture(int slot, const std::shared_ptr<Texture>& texture, FallbackTexture fallback)
    {
        check(slot >= 0);

        if (texture == nullptr)
        {
            switch (fallback)
            {
                case FallbackTexture::WHITE:
                    white_fallback_texture->bind(slot);
                    return;
                case FallbackTexture::NORMAL:
                    normal_fallback_texture->bind(slot);
                    return;
                default:
                    std::unreachable();
            }
        }

        auto odl_texture = std::dynamic_pointer_cast<OpenGLTexture>(texture);
        if (odl_texture == nullptr)
        {
            odl_texture = upload(texture);
        }
        odl_texture->bind(slot);
    }

    void OpenGLGraphicContext::bind_texture(int slot, const std::shared_ptr<CubeMap>& texture)
    {
        check(slot >= 0);

        auto odl_texture = std::dynamic_pointer_cast<OpenGLCubeMap>(texture);
        check(odl_texture != nullptr); // we don't have memory cube maps yet.
        odl_texture->bind(slot);
    }

    void OpenGLGraphicContext::draw(const std::shared_ptr<Mesh>& mesh)
    {
        auto odl_mesh = std::dynamic_pointer_cast<OpenGLMesh>(mesh);
        if (odl_mesh == nullptr)
        {
            odl_mesh = upload(mesh);
        }
        odl_mesh->draw();
    }

    void OpenGLGraphicContext::draw_fullscreen()
    {
        if (fullscreen_mesh == nullptr)
        {
            fullscreen_mesh = create_fullscreen_mesh();
        }
        draw(fullscreen_mesh);
    }

    void OpenGLGraphicContext::end_pass()
    {
        current_shader       = nullptr;
        current_frame_buffer = nullptr;

        glPopDebugGroup();
    }

    void OpenGLGraphicContext::swap_buffers()
    {
        SDL_GL_SwapWindow(window);
        collect_garbage();
    }

    std::shared_ptr<OpenGLTexture> OpenGLGraphicContext::upload(const std::shared_ptr<Texture>& texture)
    {
        auto i = texture_cache.find(texture);

        if (i != end(texture_cache))
        {
            return i->second;
        }

        auto oglt = std::make_shared<OpenGLTexture>(texture);
        texture_cache.insert_or_assign(texture, oglt);
        return oglt;
    }

    std::shared_ptr<OpenGLMesh> OpenGLGraphicContext::upload(const std::shared_ptr<Mesh>& mesh)
    {
        auto i = mesh_cache.find(mesh);

        if (i != end(mesh_cache))
        {
            return i->second;
        }

        auto oglm = std::make_shared<OpenGLMesh>(mesh);
        mesh_cache.insert_or_assign(mesh, oglm);
        return oglm;
    }

    void OpenGLGraphicContext::collect_garbage()
    {
        std::erase_if(texture_cache, [] (const auto& pair) { return pair.first.expired(); });
        std::erase_if(mesh_cache, [] (const auto& pair) { return pair.first.expired(); });
    }
}

