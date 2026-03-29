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

#include "MemoryMesh.h"

namespace pkzo
{
    MemoryMesh::MemoryMesh(MeshData&& data)
    : data(std::make_shared<MeshData>(std::move(data))) {}

    MemoryMesh::MemoryMesh(const std::shared_ptr<MeshData>& data)
    : data(data) {}

    MemoryMesh::~MemoryMesh() = default;

    const std::vector<glm::vec3>&  MemoryMesh::get_vertexes() const
    {
        return data->vertexes;
    }

    const std::vector<glm::vec3>&  MemoryMesh::get_normals() const
    {
        return data->normals;
    }

    const std::vector<glm::vec3>&  MemoryMesh::get_tangents() const
    {
        return data->tangents;
    }

    const std::vector<glm::vec2>&  MemoryMesh::get_texcoords() const
    {
        return data->texcoords;
    }

    const std::vector<glm::vec4>&  MemoryMesh::get_colors() const
    {
        return data->colors;
    }

    const std::vector<glm::uvec3>& MemoryMesh::get_faces() const
    {
        return data->faces;
    }

    const std::vector<glm::uvec2>& MemoryMesh::get_lines() const
    {
        return data->lines;
    }

    Bounds3 MemoryMesh::get_bounds() const
    {
        if (data->bounds.get_size() == glm::vec3(0.0f))
        {
            data->compute_bounds();
        }

        return data->bounds;
    }

    void MemoryMesh::update(MeshData new_data)
    {
        data = std::make_shared<MeshData>(std::move(new_data));
    }

    std::shared_ptr<MeshData> MemoryMesh::get_data() const
    {
        return data;
    }
}
