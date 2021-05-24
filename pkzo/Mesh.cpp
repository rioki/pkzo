//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Mesh.h"

#include "utils.h"
#include "Shader.h"

namespace pkzo
{
    enum Slot
    {
        POSITION,
        NORMAL,
        TEXCOORD,
        INDEX
    };

    auto get_bound_vao() noexcept
    {
        GLint id = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
        return id;
    }

    Mesh::Mesh() noexcept = default;
    Mesh::~Mesh()
    {
        if (vao != 0)
        {
            glDeleteBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
            glDeleteVertexArrays(1, &vao);
            DBG_CHECK_GLERROR("deleting vertex data");
        }
    }

    glm::uint Mesh::add_vertex(const glm::vec3 position, const glm::vec2& texcoord) noexcept
    {
        return add_vertex(position, {0.0, 0.0, 0.0}, texcoord);
    }

    glm::uint Mesh::add_vertex(const glm::vec3 position, const glm::vec3& normal, const glm::vec2& texcoord) noexcept
    {
        DBG_ASSERT(gl_id == 0); // only change mesh before upload
        vertices.push_back(position);
        normals.push_back(normal);
        texcoords.push_back(texcoord);
        return static_cast<glm::uint>(vertices.size() - 1);
    }

    void Mesh::add_triangle(const glm::uvec3& face) noexcept
    {
        DBG_ASSERT(gl_id == 0); // only change mesh before upload
        faces.push_back(face);
    }


    const std::vector<glm::vec3>& Mesh::get_vertices() const noexcept
    {
        return vertices;
    }

    const std::vector<glm::vec3>& Mesh::get_normals() const noexcept
    {
        return normals;
    }

    const std::vector<glm::vec2>& Mesh::get_texcoords() const noexcept
    {
        return texcoords;
    }

    const std::vector<glm::uvec3>& Mesh::get_faces() const noexcept
    {
        return faces;
    }

    void Mesh::upload() noexcept
    {
        DBG_ASSERT(gl_id == 0);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
        glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(float),   glm::value_ptr(normals[0]),   GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD]);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * 2 * sizeof(float), glm::value_ptr(texcoords[0]), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * 3 * sizeof(unsigned int), glm::value_ptr(faces[0]), GL_STATIC_DRAW);

        DBG_CHECK_GLERROR("uploading vertex data");
    }

    void Mesh::bind(Shader& shader) noexcept
    {
        if (vao == 0)
        {
            upload();
        }
        else
        {
            glBindVertexArray(vao);
            DBG_CHECK_GLERROR("uploading binding vertex array");
        }

        auto vertex_id = shader.get_attribute("pkzo_Vertex");
        if (vertex_id != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION]);
            glVertexAttribPointer(vertex_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(vertex_id);
            DBG_CHECK_GLERROR("uploading position");
        }
        auto normal_id = shader.get_attribute("pkzo_Normal");
        if (normal_id != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL]);
            glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(normal_id);
            DBG_CHECK_GLERROR("uploading normals");
        }
        auto texcoord_id = shader.get_attribute("pkzo_TexCoord");
        if (texcoord_id != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD]);
            glVertexAttribPointer(texcoord_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(texcoord_id);
            DBG_CHECK_GLERROR("uploading texture coordinates");
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX]);
        DBG_CHECK_GLERROR("binding mesh");
    }

    void Mesh::draw() noexcept
    {
        DBG_ASSERT(vao == get_bound_vao());
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(faces.size() * 3u), GL_UNSIGNED_INT, 0);
        DBG_CHECK_GLERROR("drawing mesh");
    }


    std::unique_ptr<Mesh> make_rectangle(const glm::vec2& size) noexcept
    {
        auto hs = size * 0.5f;
        auto mesh = std::make_unique<Mesh>();

        mesh->add_vertex({-hs.x, -hs.y, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, 0.0f}, {1.0f, 0.0f});

        mesh->add_triangle({0, 1, 2});
        mesh->add_triangle({2, 3, 0});

        return mesh;
    }
}
