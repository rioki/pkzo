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

#include "pch.h"

#include "OpenGLMesh.h"

#include "debug.h"

namespace pkzo
{
    template<glm::length_t N, glm::qualifier Q>
    std::shared_ptr<OpenGLBuffer> upload_values(AttributeLocation attr, const std::vector<glm::vec<N, float, Q>>& data, OpenGLBuffer::Usage usage)
    {
        if (data.empty())
        {
            return nullptr;
        }

        auto buffer = std::make_shared<OpenGLBuffer>(OpenGLBuffer::Type::ARRAY, usage);
        buffer->upload(data);

        buffer->bind();
        glVertexAttribPointer(std::to_underlying(attr), N, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(std::to_underlying(attr));

        return buffer;
    }

    template<glm::length_t N, glm::qualifier Q>
    void update_values(std::shared_ptr<OpenGLBuffer>& buffer, const std::vector<glm::vec<N, float, Q>>& data)
    {
        if (data.empty())
        {
            return;
        }

        check(buffer != nullptr);
        buffer->upload(data);
    }


    template<glm::length_t N, glm::qualifier Q>
    std::shared_ptr<OpenGLBuffer> upload_indexes(const std::vector<glm::vec<N, glm::uint, Q>>& data, OpenGLBuffer::Usage usage)
    {
        if (data.empty())
        {
            return {};
        }

        auto buffer = std::make_shared<OpenGLBuffer>(OpenGLBuffer::Type::ELEMENT_ARRAY, usage);
        buffer->upload(data);
        return buffer;
    }

    template<glm::length_t N, glm::qualifier Q>
    void update_indexes(std::shared_ptr<OpenGLBuffer>& buffer, const std::vector<glm::vec<N, glm::uint, Q>>& data)
    {
        if (data.empty())
        {
            return;
        }

        check(buffer != nullptr);
        buffer->upload(data);
    }

    std::shared_ptr<OpenGLMesh> OpenGLMesh::create(MeshData data, OpenGLBuffer::Usage usage)
    {
        return std::make_shared<OpenGLMesh>(std::move(data), usage);
    }

    OpenGLMesh::OpenGLMesh(MeshData&& data, OpenGLBuffer::Usage usage)
    : OpenGLMesh(std::make_shared<MeshData>(std::move(data)), usage) {}

    OpenGLMesh::OpenGLMesh(const std::shared_ptr<MeshData>& data, OpenGLBuffer::Usage usage)
    : data(data)
    {
        check(data);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        vertex_buffer   = upload_values(AttributeLocation::VERTEX,   data->vertexes,  usage);
        normal_buffer   = upload_values(AttributeLocation::NORMAL,   data->normals,   usage);
        tangent_buffer  = upload_values(AttributeLocation::TANGENT,  data->tangents,  usage);
        texcoord_buffer = upload_values(AttributeLocation::TEXCOORD, data->texcoords, usage);
        color_buffer    = upload_values(AttributeLocation::COLOR,    data->colors,    usage);

        face_buffer     = upload_indexes(data->faces, usage);
        line_buffer     = upload_indexes(data->lines, usage);
    }

    OpenGLMesh::OpenGLMesh(const std::shared_ptr<Mesh>& source)
    : OpenGLMesh(safe_ptr(source)->get_data(), OpenGLBuffer::Usage::STATIC) {}

    OpenGLMesh::~OpenGLMesh()
    {
        vertex_buffer   = nullptr;
        normal_buffer   = nullptr;
        tangent_buffer  = nullptr;
        texcoord_buffer = nullptr;
        color_buffer    = nullptr;
        face_buffer     = nullptr;
        line_buffer     = nullptr;
        glDeleteVertexArrays(1, &vao);
    }

    const std::vector<glm::vec3>&  OpenGLMesh::get_vertexes() const
    {
        return data->vertexes;
    }

    const std::vector<glm::vec3>&  OpenGLMesh::get_normals() const
    {
        return data->normals;
    }

    const std::vector<glm::vec3>&  OpenGLMesh::get_tangents() const
    {
        return data->tangents;
    }

    const std::vector<glm::vec2>&  OpenGLMesh::get_texcoords() const
    {
        return data->texcoords;
    }

    const std::vector<glm::vec4>&  OpenGLMesh::get_colors() const
    {
        return data->colors;
    }

    const std::vector<glm::uvec3>& OpenGLMesh::get_faces() const
    {
        return data->faces;
    }

    const std::vector<glm::uvec2>& OpenGLMesh::get_lines() const
    {
        return data->lines;
    }

    Bounds3 OpenGLMesh::get_bounds() const
    {
        if (data->bounds.get_size() == glm::vec3(0.0f))
        {
            data->compute_bounds();
        }

        return data->bounds;
    }

    std::shared_ptr<MeshData> OpenGLMesh::get_data() const
    {
        return data;
    }

    void OpenGLMesh::update(MeshData new_data)
    {
        data = std::make_shared<MeshData>(std::move(new_data));

        update_values(vertex_buffer,   data->vertexes);
        update_values(normal_buffer,   data->normals);
        update_values(tangent_buffer,  data->tangents);
        update_values(texcoord_buffer, data->texcoords);
        update_values(color_buffer,    data->colors);

        update_indexes(face_buffer,    data->faces);
        update_indexes(line_buffer,    data->lines);
    }

    void OpenGLMesh::draw()
    {
        glBindVertexArray(vao);

        if (!data->faces.empty())
        {
            face_buffer->bind();
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(data->faces.size() * 3u), GL_UNSIGNED_INT, nullptr);
        }

        if (!data->lines.empty())
        {
            line_buffer->bind();
            glDrawElements(GL_LINES, static_cast<GLsizei>(data->lines.size() * 2u), GL_UNSIGNED_INT, nullptr);
        }
    }
}
