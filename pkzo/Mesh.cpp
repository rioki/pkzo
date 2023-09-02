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

#include "Mesh.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "debug.h"
#include "Shader.h"

namespace pkzo
{
    std::shared_ptr<Mesh> Mesh::create_plane(const glm::vec2& size)
    {
        const auto hs = size * 0.5f;

        auto mesh = std::make_shared<Mesh>();

        mesh->add_vertex({-hs.x, -hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f});
        mesh->add_vertex({-hs.x,  hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f});
        mesh->add_vertex({ hs.x,  hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f});
        mesh->add_vertex({ hs.x, -hs.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f});

        mesh->add_triangle(0, 1, 2);
        mesh->add_triangle(0, 2, 3);

        return mesh;
    }

    Mesh::~Mesh()
    {
        release();
    }

    void Mesh::add_vertex(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& texcoord)
    {
        vertexes.push_back(vertex);
        normals.push_back(normal);
        tangents.push_back(tangent);
        texcoords.push_back(texcoord);
    }

    void Mesh::add_triangle(uint a, uint b, uint c)
    {
        triangles.push_back({a, b, c});
    }

    unsigned int Mesh::get_vertex_count() const noexcept
    {
        return vertexes.size();
    }

    unsigned int Mesh::get_triangle_count() const noexcept
    {
        return triangles.size();
    }

    void Mesh::upload()
    {
        if (is_uploaded())
        {
            return;
        }

        glGenVertexArrays(1, &vao);
        glCreateBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
        glNamedBufferData(buffers[to_underlying(BufferId::VERTEX)], vertexes.size() * sizeof(glm::vec3), glm::value_ptr(vertexes.front()), GL_STATIC_DRAW);
        glNamedBufferData(buffers[to_underlying(BufferId::NORMAL)], normals.size() * sizeof(glm::vec3), glm::value_ptr(normals[0]), GL_STATIC_DRAW);
        glNamedBufferData(buffers[to_underlying(BufferId::TANGENT)], tangents.size() * sizeof(glm::vec3), glm::value_ptr(tangents[0]), GL_STATIC_DRAW);
        glNamedBufferData(buffers[to_underlying(BufferId::TEXCOORD)], texcoords.size() * sizeof(glm::vec2), glm::value_ptr(texcoords[0]), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[to_underlying(BufferId::INDEX)]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * 3 * sizeof(unsigned int), glm::value_ptr(triangles[0]), GL_STATIC_DRAW);

        check_glerror();
    }

    bool Mesh::is_uploaded() const noexcept
    {
        return vao != 0;
    }

    void Mesh::release()
    {
        if (! is_uploaded())
        {
            return;
        }

        glDeleteBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
        glDeleteVertexArrays(1, &vao);
        check_glerror();
    }

    struct BufferInfo
    {
        BufferId    id;
        std::string name;
        uint        size;
    };
    const auto buffer_infos = std::array<BufferInfo, buffer_count - 1>{
        BufferInfo{BufferId::VERTEX,   "pkzo_Vertex",   3},
        BufferInfo{BufferId::NORMAL,   "pkzo_Normal",   3},
        BufferInfo{BufferId::TANGENT,  "pkzo_Tangent",  3},
        BufferInfo{BufferId::TEXCOORD, "pkzo_TexCoord", 2}
    };

    void Mesh::bind(std::shared_ptr<Shader> shader)
    {
        check(shader != nullptr);

        if (!is_uploaded())
        {
            upload();
        }

        glBindVertexArray(vao);

        for (const auto& [id, name, size] : buffer_infos)
        {
            auto adr = shader->get_attribute(name);
            if (adr != -1)
            {
                glBindBuffer(GL_ARRAY_BUFFER, buffers[to_underlying(id)]);
                glVertexAttribPointer(adr, size, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(adr);
                check_glerror();
            }
        }

        check_glerror();
    }

    void Mesh::draw()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[to_underlying(BufferId::INDEX)]);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(triangles.size() * 3u), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Mesh::draw(std::shared_ptr<Shader> shader)
    {
        bind(shader);
        draw();
    }
}

