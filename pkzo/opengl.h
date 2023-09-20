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

#pragma once
#include "config.h"

#include <memory>
#include <source_location>
#include <string_view>
#include <variant>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

namespace pkzo::opengl
{
    using namespace glm;

    PKZO_EXPORT void clear_glerrors() noexcept;
    PKZO_EXPORT void check_glerror(const std::source_location location = std::source_location::current()) noexcept;

    class PKZO_EXPORT Section
    {
    public:
        explicit Section(const std::string_view id);
        ~Section();

    private:
        Section(const Section&) = delete;
        Section& operator = (const Section&) = delete;
    };

    enum class ShaderType : GLenum
    {
        COMPUTE_SHADER         = GL_COMPUTE_SHADER,
        VERTEX_SHADER          = GL_VERTEX_SHADER,
        TESS_CONTROL_SHADER    = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
        GEOMETRY_SHADER        = GL_GEOMETRY_SHADER,
        FRAGMENT_SHADER        = GL_FRAGMENT_SHADER
    };

    using UniformValue = std::variant<bool, int, uint, float,
                                      ivec2, uvec2, vec2,
                                      ivec3, uvec3, vec3,
                                      ivec4, uvec4, vec4,
                                      mat2,  mat3,  mat4>;

    class PKZO_EXPORT Shader
    {
    public:
        Shader();
        ~Shader();

        void compile(ShaderType type, const std::vector<const char*>& code, std::ostream& log);
        void link(std::ostream& log);

        void bind();

        void set_uniform(const std::string_view name, const UniformValue& value) noexcept;

    private:
        uint program_id = 0;
        std::vector<uint> shader_ids;

        Shader(const Shader&) = delete;
        Shader& operator = (const Shader&) = delete;
    };

    enum class BufferUsage : GLenum
    {
        STREAM_DRAW  = GL_STREAM_DRAW,
        STREAM_READ  = GL_STREAM_READ,
        STREAM_COPY  = GL_STREAM_COPY,
        STATIC_DRAW  = GL_STATIC_DRAW,
        STATIC_READ  = GL_STATIC_READ,
        STATIC_COPY  = GL_STATIC_COPY,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        DYNAMIC_READ = GL_DYNAMIC_READ,
        DYNAMIC_COPY = GL_DYNAMIC_COPY
    };

    class PKZO_EXPORT Buffer
    {
    public:
        Buffer(const void* data, const uint size, BufferUsage usage = BufferUsage::STATIC_DRAW);
        ~Buffer();

        uint get_id() const noexcept;
        uint get_size() const noexcept;

    private:
        uint id     = 0u;
        uint size   = 0u;

        Buffer(const Buffer&) = delete;
        Buffer& operator = (const Buffer&) = delete;
    };

    enum class ColorMode
    {
        R               = GL_R,
        RG              = GL_RG,
        RGB             = GL_RGB,
        BGR             = GL_BGR,
        RGBA            = GL_RGBA,
        BGRA            = GL_BGRA,
        DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
        STENCIL_INDEX   = GL_STENCIL_INDEX
    };

    //! Data Type
    enum class DataType
    {
        UNSIGNED_BYTE  = GL_UNSIGNED_BYTE,
        BYTE           = GL_BYTE,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        SHORT          = GL_SHORT,
        UNSIGNED_INT   = GL_UNSIGNED_INT,
        INT            = GL_INT,
        FLOAT          = GL_FLOAT,
        DOUBLE         = GL_DOUBLE
    };

    enum class FilterMode : GLenum
    {
        NEAREST = GL_NEAREST,
        LINEAR  = GL_LINEAR
    };

    enum class WrapMode : GLenum
    {
        CLAMP_TO_EDGE        = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER      = GL_CLAMP_TO_BORDER,
        MIRRORED_REPEAT      = GL_MIRRORED_REPEAT,
        REPEAT               = GL_REPEAT,
        MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
    };

    class Texture
    {
    public:
        Texture(const std::string& label = "unnamed");
        ~Texture();

        void upload(uvec2 size, ColorMode color, DataType type, const void* bits = nullptr, FilterMode filter = FilterMode::LINEAR, WrapMode wrap = WrapMode::REPEAT);

        void bind(uint slot);

    private:
        uint        id;
        std::string label;

        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
    };

    enum class FacesType : GLenum
    {
        POINTS          = GL_POINTS,
        LINES           = GL_LINES,
        LINE_STRIP      = GL_LINE_STRIP,
        LINE_LOOP       = GL_LINE_LOOP,
        TRIANGLES       = GL_TRIANGLES,
        TRIANGLE_STRIP  = GL_TRIANGLE_STRIP,
        TRIANGLE_FAN    = GL_TRIANGLE_FAN
    };

    class PKZO_EXPORT VertexBuffer
    {
    public:
        VertexBuffer(const std::string_view label = "unnamed");
        ~VertexBuffer();

        uint get_id() const noexcept;
        uint get_size() const noexcept;

        void upload_values(uint stride, uint count, const float* data) noexcept;

        template <int N, qualifier Q>
        void upload_values(const std::vector<vec<N, float, Q>>& values) noexcept;

        std::shared_ptr<Buffer> get_buffer(uint index) noexcept;
        std::shared_ptr<const Buffer> get_buffer(uint index) const noexcept;

        void upload_indexes(FacesType type, uint count, const uint* data) noexcept;

        template <int N, qualifier Q>
        void upload_indexes(const std::vector<vec<N, glm::uint, Q>>& indexes) noexcept;

        void draw();

    private:
        uint                                 id     = 0u;
        std::vector<std::shared_ptr<Buffer>> buffers;
        std::shared_ptr<Buffer>              indexes;
        FacesType                            face_type;
        uint                                 index_count;
    };

    template <int N, glm::qualifier Q>
    void VertexBuffer::upload_values(const std::vector<vec<N, float, Q>>& values) noexcept
    {
        upload_values(N, static_cast<uint>(values.size()), glm::value_ptr(values[0]));
    }

    constexpr FacesType get_face_type(uint N) noexcept
    {
        switch (N)
        {
        case 1:
            return FacesType::POINTS;
        case 2:
            return FacesType::LINES;
        case 3:
            return FacesType::TRIANGLES;
        case 4:
            fail("OpenGL does not support vertex buffers with quads.");
        default:
            fail("Unknown index type.");
        }
    }

    template <int N, glm::qualifier Q>
    void VertexBuffer::upload_indexes(const std::vector<vec<N, uint, Q>>& indexes) noexcept
    {
        auto type = get_face_type(N);
        upload_indexes(type, static_cast<uint>(indexes.size()) * N, glm::value_ptr(indexes[0]));
    }
}
