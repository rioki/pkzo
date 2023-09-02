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

#include <array>
#include <filesystem>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "utils.h"

namespace pkzo
{
    using namespace glm;

    class Shader;

    enum class BufferId : uint
    {
        VERTEX,
        NORMAL,
        TANGENT,
        TEXCOORD,
        INDEX,
        MAX
    };
    constexpr auto buffer_count = to_underlying(BufferId::MAX);

    class PKZO_EXPORT Mesh
    {
    public:
        static std::shared_ptr<Mesh> load_file(const std::filesystem::path& file);
        static std::shared_ptr<Mesh> create_plane(const glm::vec2& size);

        Mesh() = default;
        Mesh(const std::filesystem::path& file);
        ~Mesh();

        void add_vertex(const glm::vec3& vertex, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& texcoords);
        void add_triangle(uint a, uint b, uint c);

        void upload();
        bool is_uploaded() const noexcept;
        void free_videomemory();
        void bind(std::shared_ptr<Shader> shader);
        void draw();
        void draw(std::shared_ptr<Shader> shader);

    private:
        // TODO: check if glm::vec4 provides better performance
        std::vector<glm::vec3>         vertices;
        std::vector<glm::vec3>         normals;
        std::vector<glm::vec3>         tangents;
        std::vector<glm::vec2>         texcoords;

        std::vector<glm::uvec3>        indexes;

        uint                           vao = 0;
        std::array<uint, buffer_count> buffers;
    };
}

