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

#include <filesystem>

#include <glm/glm.hpp>

#include "Mesh.h"

namespace pkzo
{
    class PKZO_EXPORT MemoryMesh : public Mesh
    {
    public:
        MemoryMesh(MeshData&& data);
        MemoryMesh(const std::shared_ptr<MeshData>& data);
        ~MemoryMesh();

        const std::vector<glm::vec3>&  get_vertexes() const override;
        const std::vector<glm::vec3>&  get_normals() const override;
        const std::vector<glm::vec3>&  get_tangents() const override;
        const std::vector<glm::vec2>&  get_texcoords() const override;
        const std::vector<glm::vec4>&  get_colors() const override;
        const std::vector<glm::uvec3>& get_faces() const override;
        const std::vector<glm::uvec2>& get_lines() const override;

        Bounds3 get_bounds() const override;

        void update(MeshData new_data) override;

        std::shared_ptr<MeshData> get_data() const override;

    private:
        std::shared_ptr<MeshData> data;
    };
}
