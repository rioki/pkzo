// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "opengl.h"

#include <array>

#include "debug.h"
#include "utils.h"

namespace pkzo::opengl
{
    void clear_glerrors() noexcept
    {
        auto e = GLenum{};
        do
        {
            e = glGetError();
        }
        while (e != GL_NO_ERROR);
    }

    const char* gl_error_to_string(unsigned int glerror) noexcept
    {
        switch (glerror)
        {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        default:
            fail("Unknown glerror type");
            return "UNKNOWN";
        }
    }

    void check_glerror(const std::source_location location) noexcept
    {
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            fail(std::format("OpenGL Error: {}!", gl_error_to_string(error)));
        }
    }

    Section::Section(const std::string_view id)
    {
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, id.data());
        check_glerror();
    }

    Section::~Section()
    {
        glPopDebugGroup();
        check_glerror();
    }

    constexpr const char* source_to_string(GLenum source) noexcept {
      switch (source) {
        case GL_DEBUG_SOURCE_API:
          return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
          return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
          return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
          return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:
          return "Application";
        case GL_DEBUG_SOURCE_OTHER:
          return "Other";
        default:
          return "Unknown";
      }
    }

    constexpr const char* type_to_string(GLenum type) noexcept {
      switch (type) {
        case GL_DEBUG_TYPE_ERROR:
          return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
          return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
          return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY:
          return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:
          return "Performance";
        case GL_DEBUG_TYPE_OTHER:
          return "Other";
        case GL_DEBUG_TYPE_MARKER:
          return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:
          return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
          return "Pop Group";
        default:
          return "Unknown";
      }
    }

    constexpr const char* severity_to_string(GLenum severity) noexcept {
      switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
          return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:
          return "Medium";
        case GL_DEBUG_SEVERITY_LOW:
          return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
          return "Notification";
        default:
          return "Unknown";
      }
    }

    void GLAPIENTRY trace_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
       const auto source_str   = source_to_string(source);
       const auto type_str     = type_to_string(type);
       const auto severity_str = severity_to_string(severity);

        std::string formatted_message = std::format(
            "OpenGL Debug [Source: {}, Type: {}, ID: {}, Severity: {}]: {}",
            source_str, type_str, id, severity_str, message);

        trace(formatted_message);
    }

    Trace::Trace()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(trace_callback, nullptr);
    }

    Trace::~Trace()
    {
        glDisable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(nullptr, nullptr);
    }

    Shader::Shader() = default;

    Shader::~Shader()
    {
        if (!shader_ids.empty())
        {
            for (const auto shader_id : shader_ids)
            {
                 glDeleteShader(shader_id);
            }
            check_glerror();
        }

        if (program_id != 0)
        {
            glDeleteProgram(program_id);
            program_id = 0;
            check_glerror();
        }
    }

    void Shader::compile(ShaderType type, const std::vector<const char*>& code, std::ostream& log)
    {
        auto status = 0;
        auto logstr = std::array<char, 256>();

        unsigned int shader_id = glCreateShader(to_underlying(type));
        glShaderSource(shader_id, static_cast<GLsizei>(code.size()), code.data(), nullptr);
        glCompileShader(shader_id);

        glGetShaderInfoLog(shader_id, static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glDeleteShader(shader_id);
            throw std::runtime_error("Failed to compile shader.");
        }

        check_glerror();
        shader_ids.push_back(shader_id);
    }

    void Shader::link(std::ostream& log)
    {
        check(program_id == 0);
        check(shader_ids.size() != 0);

        auto status = 0;
        auto logstr = std::array<char, 256>();

        program_id = glCreateProgram();
        for (const auto shader_id : shader_ids)
        {
             glAttachShader(program_id, shader_id);
        }
        glLinkProgram(program_id);
        check_glerror();

        glGetProgramInfoLog(program_id,  static_cast<GLsizei>(logstr.size()), nullptr, logstr.data());
        log << logstr.data();

        glGetProgramiv(program_id, GL_LINK_STATUS, &status);
        if (!status)
        {
            throw std::runtime_error("Failed to link shader program.");
        }

        // NOTE: glDeleteShader() actually does not delete the shader, it only
        // flags the shader for deletion. The shaders will be deleted when
        // the program gets deleted.
        for (const auto shader_id : shader_ids)
        {
            glDeleteShader(shader_id);
        }
        check_glerror();
        shader_ids.clear();
    }

    void Shader::bind()
    {
        check(program_id != 0);
        glUseProgram(program_id);
        check_glerror();
    }

    void Shader::set_uniform(const std::string_view name, const UniformValue& value) noexcept
    {
        check_glerror();
        check(program_id != 0);
        auto location = glGetUniformLocation(program_id, name.data());
        check_glerror();
        if (location != -1)
        {
            std::visit(overloaded {
                [&] (bool v)         { glProgramUniform1i(program_id, location, v); },
                [&] (int v)          { glProgramUniform1i(program_id, location, v); },
                [&] (uint v)         { glProgramUniform1i(program_id, location, v); },
                [&] (float v)        { glProgramUniform1f(program_id, location, v); },
                [&] (const ivec2& v) { glProgramUniform2i(program_id, location, v.x, v.y); },
                [&] (const uvec2& v) { glProgramUniform2i(program_id, location, v.x, v.y); },
                [&] (const vec2& v)  { glProgramUniform2f(program_id, location, v.x, v.y); },
                [&] (const ivec3& v) { glProgramUniform3i(program_id, location, v.x, v.y, v.z); },
                [&] (const uvec3& v) { glProgramUniform3i(program_id, location, v.x, v.y, v.z); },
                [&] (const vec3& v)  { glProgramUniform3f(program_id, location, v.x, v.y, v.z); },
                [&] (const ivec4& v) { glProgramUniform4i(program_id, location, v.x, v.y, v.z, v.w); },
                [&] (const uvec4& v) { glProgramUniform4i(program_id, location, v.x, v.y, v.z, v.w); },
                [&] (const vec4& v)  { glProgramUniform4f(program_id, location, v.x, v.y, v.z, v.w); },
                [&] (const mat2& v)  { glProgramUniformMatrix2fv(program_id, location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const mat3& v)  { glProgramUniformMatrix3fv(program_id, location, 1u, GL_FALSE, glm::value_ptr(v)); },
                [&] (const mat4& v)  { glProgramUniformMatrix4fv(program_id, location, 1u, GL_FALSE, glm::value_ptr(v)); }
            }, value);
            check_glerror();
        }
    }

    Buffer::Buffer(const void* data, const uint _size, BufferUsage usage, const std::string_view label)
    : size(_size)
    {
         glCreateBuffers(1, &id);
         glNamedBufferData(id, size, data, to_underlying(usage));
         //glObjectLabel(id, GL_BUFFER, label.size(), label.data());
         check_glerror();
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &id);
        check_glerror();
    }

    uint Buffer::get_id() const noexcept
    {
        return id;
    }

    uint Buffer::get_size() const noexcept
    {
        return size;
    }

    Texture::Texture(const std::string& _label)
    : label(_label)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        check_glerror();
    }

    Texture::~Texture()
    {
        check(id != 0);
        glDeleteTextures(1, &id);
        check_glerror();
    }


    GLenum get_internal_format(ColorMode color, DataType data) noexcept
    {
        switch (data)
        {
        case DataType::BYTE:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R8I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB8I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA8I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA8I;
            }
        case DataType::UNSIGNED_BYTE:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_RED;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB8;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA8;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA8UI;
            }
        case DataType::SHORT:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R16I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB16I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA16I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA16I;
            }
        case DataType::UNSIGNED_SHORT:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R16UI;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB16UI;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA16UI;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA16UI;
            }
        case DataType::INT:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R32I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32I;
            }
        case DataType::UNSIGNED_INT:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R32UI;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32UI;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32UI;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32UI;
            }
        case DataType::FLOAT:
        case DataType::DOUBLE:
            switch (color)
            {
            case ColorMode::GRAYSCALE:
                return GL_R32F;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32F;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32F;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32F;
            }
        default:
            fail("Unexpected type.");
            return GL_RGB;
        }
    }

    void Texture::upload(uvec2 size, ColorMode color, DataType type, const void* bits, FilterMode filter, WrapMode wrap)
    {
        auto gl_internalformat = get_internal_format(color, type);
        auto gl_format         = to_underlying(color);
        auto gl_type           = to_underlying(type);

        glTextureStorage2D(id, 1, gl_internalformat, size.x, size.y);
        check_glerror();

        glTextureSubImage2D(id, 0, 0, 0, size.x, size.y, gl_format, gl_type, bits);
        check_glerror();

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, to_underlying(filter));
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, to_underlying(filter));
        glTextureParameteri(id, GL_TEXTURE_WRAP_S,     to_underlying(wrap));
        glTextureParameteri(id, GL_TEXTURE_WRAP_T,     to_underlying(wrap));
        check_glerror();
    }

    void Texture::bind(uint slot)
    {
        glBindTextureUnit(slot, id);  // DSA
        check_glerror();
    }

    VertexBuffer::VertexBuffer(const std::string_view label)
    {
        glGenVertexArrays(1, &id);
        //glObjectLabel(GL_VERTEX_ARRAY, id, static_cast<GLsizei>(label.size()), label.data());
        check_glerror();
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteVertexArrays(1, &id);
        check_glerror();
    }

    uint VertexBuffer::get_id() const noexcept
    {
        return id;
    }

    uint VertexBuffer::get_size() const noexcept
    {
        auto total = 0u;
        for (const auto& buffer : buffers)
        {
            total += buffer->get_size();
        }
        return total;
    }

    void VertexBuffer::upload_values(uint stride, uint count, const float* data) noexcept
    {
        auto buffer = std::make_shared<Buffer>(data, static_cast<uint>(count * stride * sizeof(float)));

        glBindVertexArray(id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer->get_id());
        glEnableVertexAttribArray(static_cast<GLuint>(buffers.size()));
        glVertexAttribPointer(static_cast<GLuint>(buffers.size()), stride, GL_FLOAT, GL_FALSE, 0, nullptr);
        check_glerror();

        buffers.push_back(buffer);
    }

    std::shared_ptr<Buffer> VertexBuffer::get_buffer(uint index) noexcept
    {
        check(index < buffers.size());
        return buffers[index];
    }

    std::shared_ptr<const Buffer> VertexBuffer::get_buffer(uint index) const noexcept
    {
        check(index < buffers.size());
        return buffers[index];
    }

    void VertexBuffer::upload_indexes(FacesType type, uint count, const uint* data) noexcept
    {
        check(indexes == nullptr);

        face_type   = type;
        index_count = count;
        indexes = std::make_shared<Buffer>(data, static_cast<uint>(count * sizeof(uint)));

        glBindVertexArray(id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes->get_id());
        check_glerror();
    }

    void VertexBuffer::draw()
    {
        check(indexes != nullptr);

        glBindVertexArray(id);
        glDrawElements(to_underlying(face_type), index_count, GL_UNSIGNED_INT, nullptr);
        check_glerror();
    }
}
