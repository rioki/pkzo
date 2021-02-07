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

#include "Shader.h"

namespace pkzo
{
    enum Slot
    {
        POSITION,
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

    }

    glm::uint Mesh::add_vertex(const glm::vec3 position, const glm::vec2& texcoord) noexcept
    {
        assert(gl_id == 0); // only change mesh before upload
        positions.push_back(position);
        texcoords.push_back(texcoord);
        return positions.size() - 1;
    }

    void Mesh::add_triangle(const glm::uvec3& face) noexcept
    {
        assert(gl_id == 0); // only change mesh before upload
        indexes.push_back(face);
    }

    void Mesh::upload() noexcept
    {
        assert(gl_id == 0);
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(buffers.size(), buffers.data());
        glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION]);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * 3 * sizeof(float), glm::value_ptr(positions[0]), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD]);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * 2 * sizeof(float), glm::value_ptr(texcoords[0]), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * 3 * sizeof(unsigned int), glm::value_ptr(indexes[0]), GL_STATIC_DRAW);

        assert(glGetError() == GL_NO_ERROR);
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
            assert(glGetError() == GL_NO_ERROR);
        }

        auto vertex_id = shader.get_attribute("pkzo_Vertex");
        if (vertex_id != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION]);
            glVertexAttribPointer(vertex_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(vertex_id);
            assert(glGetError() == GL_NO_ERROR);
        }
        auto texcoord_id = shader.get_attribute("pkzo_TexCoord");
        if (texcoord_id != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD]);
            glVertexAttribPointer(texcoord_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(texcoord_id);
            assert(glGetError() == GL_NO_ERROR);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX]);
        assert(glGetError() == GL_NO_ERROR);
    }

    void Mesh::draw() noexcept
    {
        assert(vao == get_bound_vao());
        glDrawElements(GL_TRIANGLES, indexes.size() * 3u, GL_UNSIGNED_INT, 0);
    }
}
