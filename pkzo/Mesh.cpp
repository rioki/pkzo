
#include "Mesh.h"

#include <GL/glew.h>

#include "Shader.h"
#include "PlyParser.h"

namespace pkzo
{
    enum BufferId
    {
        VERTEX_BUFFER   = 0,
        NORMAL_BUFFER   = 1,
        TEXCOORD_BUFFER = 2,
        TANGENT_BUFFER  = 3,
        COLOR_BUFFER    = 4,
        INDEX_BUFFER    = 5
    };
    
    Mesh::Mesh()
    : vao(0) {}

    Mesh::~Mesh()
    {
        release();
    }

    void Mesh::set_vertex_count(size_t value)
    {
        vertices.resize(value * 3);
        normals.resize(value * 3);
        texcoords.resize(value * 2);
        tangents.resize(value * 3);
        colors.resize(value * 4);
    }

    void Mesh::load(const std::string& file)
    {
        PlyParser parser(*this);
        parser.parse(file);
    }

    void Mesh::create_plane(float width, float height)
    {
        float w2 = width / 2.0f;
        float h2 = height / 2.0f;

        set_vertex_count(4);

        set_vertex(0, -w2, -h2, 0.0f);
        set_vertex(1, -w2,  h2, 0.0f);
        set_vertex(2,  w2,  h2, 0.0f);
        set_vertex(3,  w2, -h2, 0.0f);

        set_normal(0, 0.0f, 0.0f, 1.0f);
        set_normal(1, 0.0f, 0.0f, 1.0f);
        set_normal(2, 0.0f, 0.0f, 1.0f);
        set_normal(3, 0.0f, 0.0f, 1.0f);

        set_texcoord(0, 0.0f, 0.0f);
        set_texcoord(1, 0.0f, 1.0f);
        set_texcoord(2, 1.0f, 1.0f);
        set_texcoord(3, 1.0f, 0.0f);

        set_tangent(0, 1.0f, 0.0f, 0.0f);
        set_tangent(1, 1.0f, 0.0f, 0.0f);
        set_tangent(2, 1.0f, 0.0f, 0.0f);
        set_tangent(3, 1.0f, 0.0f, 0.0f);

        set_color(0, 1.0f, 1.0f, 1.0f, 1.0f);
        set_color(1, 1.0f, 1.0f, 1.0f, 1.0f);
        set_color(2, 1.0f, 1.0f, 1.0f, 1.0f);
        set_color(3, 1.0f, 1.0f, 1.0f, 1.0f);

        set_face_count(2);
        set_face(0, 0, 2, 1);
        set_face(1, 0, 3, 2);
    }

    size_t Mesh::get_vertex_count() const
    {
        return vertices.size() / 3;
    }

    void Mesh::set_vertex(size_t i, float x, float y, float z)
    {
        size_t b = i * 3;
        vertices[b + 0] = x;
        vertices[b + 1] = y;
        vertices[b + 2] = z;
    }

    std::tuple<float, float, float> Mesh::get_vertex(size_t i) const
    {
        size_t b = i * 3;
        return std::make_tuple(vertices[b + 0], vertices[b + 1], vertices[b + 2]);
    }

    void Mesh::set_normal(size_t i, float x, float y, float z)
    {
        size_t b = i * 3;
        normals[b + 0] = x;
        normals[b + 1] = y;
        normals[b + 2] = z;
    }

    std::tuple<float, float, float> Mesh::get_normal(size_t i) const
    {
        size_t b = i * 3;
        return std::make_tuple(normals[b + 0], normals[b + 1], normals[b + 2]);
    }

    void Mesh::set_texcoord(size_t i, float u, float v)
    {
        size_t b = i * 2;
        texcoords[b + 0] = u;
        texcoords[b + 1] = v;
    }

    std::tuple<float, float> Mesh::get_texcoord(size_t i) const
    {
        size_t b = i * 2;
        return std::make_tuple(texcoords[b + 0], texcoords[b + 1]);
    }

    void Mesh::set_tangent(size_t i, float x, float y, float z)
    {
        size_t b = i * 3;
        tangents[b + 0] = x;
        tangents[b + 1] = y;
        tangents[b + 2] = z;
    }

    std::tuple<float, float, float> Mesh::get_tangent(size_t i) const
    {
        size_t b = i * 3;
        return std::make_tuple(tangents[b + 0], tangents[b + 1], tangents[b + 2]);
    }

    void Mesh::set_color(size_t i, float r, float g, float b, float a)
    {
        size_t ba = i * 4;
        colors[ba + 0] = r;
        colors[ba + 1] = g;
        colors[ba + 2] = b;
        colors[ba + 3] = a;
    }

    std::tuple<float, float, float, float> Mesh::get_color(size_t i) const
    {
        size_t b = i * 4;
        return std::make_tuple(colors[b + 0], colors[b + 1], colors[b + 2], colors[b + 3]);
    }

    void Mesh::set_face_count(size_t value)
    {
        faces.resize(value * 3);
    }

    size_t Mesh::get_face_count() const
    {
        return faces.size() / 3;
    }

    void Mesh::set_face(size_t i, unsigned int a, unsigned int b, unsigned int c)
    {
        size_t ba = i * 3;
        faces[ba + 0] = a;
        faces[ba + 1] = b;
        faces[ba + 2] = c;
    }

    void Mesh::add_face(unsigned int a, unsigned int b, unsigned int c)
    {
        faces.push_back(a);
        faces.push_back(b);
        faces.push_back(c);
    }

    std::tuple<unsigned int, unsigned int, unsigned int> Mesh::get_face(size_t i) const
    {
        size_t b = i * 3;
        return std::make_tuple(faces[b + 0], faces[b + 1], faces[b + 2]);
    }

    // void Mesh::compute_normals();

    // void Mesh::compute_tangents();

    void Mesh::upload()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(6, buffers);

        size_t vcount = get_vertex_count();
        size_t fcount = get_face_count();

        glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 2 * sizeof(float), &texcoords[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[TANGENT_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &tangents[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[COLOR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 4 * sizeof(float), &colors[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, fcount * 3 * sizeof(unsigned int), &faces[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Mesh::release()
    {
        if (vao != 0)
        {
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(6, buffers);
            vao = 0;
        }        
    }

    void Mesh::draw(Shader& shader) const
    {
        if (vao == 0)
        {
            const_cast<Mesh*>(this)->upload();
        }

        shader.bind(); // this is probably redundant

        int vertex_location   = shader.get_attribute_location("aVertex");
        int normal_location   = shader.get_attribute_location("aNormal");
        int texcoord_location = shader.get_attribute_location("aTexCoord");
        int tangent_location  = shader.get_attribute_location("aTangent");
        int color_location    = shader.get_attribute_location("aColor");

        glBindVertexArray(vao);

        if (vertex_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
            glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(vertex_location);
        }

        if (normal_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
            glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(normal_location);
        }

        if (texcoord_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
            glVertexAttribPointer(texcoord_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(texcoord_location);
        }

        if (tangent_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[TANGENT_BUFFER]);
            glVertexAttribPointer(tangent_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(tangent_location);
        }

        if (color_location != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[COLOR_BUFFER]);
            glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(color_location);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        if (vertex_location != -1)
        {
            glDisableVertexAttribArray(vertex_location);
        }

        if (normal_location != -1)
        {
            glDisableVertexAttribArray(normal_location);
        }

        if (texcoord_location != -1)
        {
            glDisableVertexAttribArray(texcoord_location);
        }

        if (texcoord_location != -1)
        {
            glDisableVertexAttribArray(tangent_location);
        }

        if (color_location != -1)
        {
            glDisableVertexAttribArray(color_location);
        }

        glBindVertexArray(0);
    }
}
