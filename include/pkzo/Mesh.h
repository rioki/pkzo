
#ifndef _PKZO_MESH_H_
#define _PKZO_MESH_H_

#include <tuple>
#include <vector>

#include "defines.h"

namespace pkzo
{
    class Shader;

    class PKZO_EXPORT Mesh
    {
    public:

        Mesh();

        Mesh(const Mesh&) = delete;

        ~Mesh();

        const Mesh& operator = (const Mesh&) = delete;

        void load(const std::string& file);

        void create_plane(float width, float height);

        void set_vertex_count(size_t value);

        size_t get_vertex_count() const;

        void set_vertex(size_t i, float x, float y, float z);

        std::tuple<float, float, float> get_vertex(size_t i) const;

        void set_normal(size_t i, float x, float y, float z);

        std::tuple<float, float, float> get_normal(size_t i) const;

        void set_texcoord(size_t i, float u, float v);

        std::tuple<float, float> get_texcoord(size_t i) const;

        void set_tangent(size_t i, float x, float y, float z);

        std::tuple<float, float, float> get_tangent(size_t i) const;

        void set_color(size_t i, float r, float g, float b, float a);

        std::tuple<float, float, float, float> get_color(size_t i) const;

        void set_face_count(size_t value);

        size_t get_face_count() const;

        void set_face(size_t i, unsigned int a, unsigned int b, unsigned int c);

        void add_face(unsigned int a, unsigned int b, unsigned int c);

        std::tuple<unsigned int, unsigned int, unsigned int> get_face(size_t i) const;

        // void compute_normals();

        // void compute_tangents();

        void upload();

        void release();

        void draw(Shader& shader) const;

    private:
        std::vector<float> vertices;  // v3f
        std::vector<float> normals;   // v3f
        std::vector<float> texcoords; // v2f
        std::vector<float> tangents;  // v3f
        std::vector<float> colors;     // v4f

        std::vector<unsigned int> faces;       // v3i

        unsigned int vao;
        unsigned int buffers[6];
    };
}

#endif

 
