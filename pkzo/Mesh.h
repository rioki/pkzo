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

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "api.h"
#include "Bounds.h"

namespace pkzo
{
    struct MeshData
    {
        std::vector<glm::vec3>  vertexes;
        std::vector<glm::vec3>  normals;
        std::vector<glm::vec3>  tangents;
        std::vector<glm::vec2>  texcoords;
        std::vector<glm::vec4>  colors;
        std::vector<glm::uvec3> faces;
        std::vector<glm::uvec2> lines;
        Bounds                  bounds;

        void compute_bounds();
    };

    class PKZO_EXPORT Mesh
    {
    public:
        static std::shared_ptr<Mesh> create(MeshData specs);

        Mesh() = default;
        virtual ~Mesh() = default;

        virtual const std::vector<glm::vec3>&  get_vertexes() const = 0;
        virtual const std::vector<glm::vec3>&  get_normals() const = 0;
        virtual const std::vector<glm::vec3>&  get_tangents() const = 0;
        virtual const std::vector<glm::vec2>&  get_texcoords() const = 0;
        virtual const std::vector<glm::vec4>&  get_colors() const = 0;
        virtual const std::vector<glm::uvec3>& get_faces() const = 0;
        virtual const std::vector<glm::uvec2>& get_lines() const = 0;

        virtual Bounds get_bounds() const = 0;

        virtual void update(MeshData new_data) = 0;

        virtual std::shared_ptr<MeshData> get_data() const = 0;

    private:
        Mesh(const Mesh&) = delete;
        Mesh& operator = (const Mesh&) = delete;
    };
}
