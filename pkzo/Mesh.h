// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MESH_H_
#define _PKZO_MESH_H_

#include <memory>
#include <vector>
#include <tuple>
#include <string>
#include <filesystem>
#include <glm/glm.hpp>
#include "defines.h"

namespace fs = std::filesystem;

namespace pkzo
{
    class Shader;

    class PKZO_EXPORT Mesh
    {
    public:

        //! Create a rectangle mesh.
        static std::shared_ptr<Mesh> create_rectangle(glm::vec2 size, bool flip_y_uv = false);

        //! Create a rectangle mesh that can be used for fullscreen blitting.
        static std::shared_ptr<Mesh> create_fullscreen_rectangle();

        //! Create a box mesh.
        static std::shared_ptr<Mesh> create_box(glm::vec3 size);

        Mesh();

        Mesh(const fs::path& file);

        Mesh(const Mesh&) = delete;

        ~Mesh();

        const Mesh& operator = (const Mesh&) = delete;

        void set_vertex_count(size_t value);

        size_t get_vertex_count() const;

        void set_vertex(size_t i, const glm::vec3& v);

        glm::vec3 get_vertex(size_t i) const;

        void set_normal(size_t i, const glm::vec3& v);

        glm::vec3 get_normal(size_t i) const;

        void set_texcoord(size_t i, const glm::vec2& v);

        glm::vec2 get_texcoord(size_t i) const;

        void set_tangent(size_t i, const glm::vec3& v);

        glm::vec3 get_tangent(size_t i) const;

        void set_face_count(size_t value);

        size_t get_face_count() const;

        void set_face(size_t i, unsigned int a, unsigned int b, unsigned int c);

        void add_face(unsigned int a, unsigned int b, unsigned int c);

        glm::uvec3 get_face(size_t i) const;

        //! Set the number of lines.
        void set_line_count(size_t value);
        //! Get the number of lines.
        size_t get_line_count() const;
        //! Set a line
        void set_line(size_t i, const glm::uvec2& value);
        //! Get a line.
        glm::uvec2 get_line(size_t i) const;

        void compute_normals();

        void compute_tangents();

        std::tuple<glm::vec3, glm::vec3> get_bounds() const;

        std::tuple<glm::vec3, float> get_bounding_sphere() const;

        void bind(Shader& shader);

        void unbind();

        void draw();

        //! Get array of vertexes.
        const std::vector<glm::vec3>& get_vertexes() const;
        //! Get array of normals
        const std::vector<glm::vec3>& get_normals() const;
        //! Get array of texture coordinates.
        const std::vector<glm::vec2>& get_texcoords() const;
        //! Get array of tangents.
        const std::vector<glm::vec3>& get_tangents() const;
        //! Get array of triangle indexes.
        const std::vector<glm::uvec3>& get_faces() const;
        //! Get array of line indexes.
        const std::vector<glm::uvec2>& get_lines() const;

    private:
        glm::vec3 min;
        glm::vec3 max;

        std::vector<glm::vec3> vertexes;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::vec3> tangents;

        std::vector<glm::uvec3> faces;
        std::vector<glm::uvec2> lines;

        bool      bound = false;
        glm::uint vao = 0;
        glm::uint vertex_buffer = 0;
        glm::uint normal_buffer = 0;
        glm::uint texcoord_buffer = 0;
        glm::uint tangent_buffer = 0;
        glm::uint face_buffer = 0;
        glm::uint line_buffer = 0;

        void load_ply(const fs::path& file);
        void load_obj(const fs::path& file);
        void upload();
    };
}

#endif


