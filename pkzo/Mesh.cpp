
#include "Mesh.h"

#include <GL/glew.h>

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
        vertices.resize(value * 4);
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

    void Mesh::create_screen_plane()
    {
        set_vertex_count(4);

        set_vertex(0, rgm::vec3(-1.0f, -1.0f, 0.0f));
        set_vertex(1, rgm::vec3(-1.0f,  1.0f, 0.0f));
        set_vertex(2, rgm::vec3( 1.0f,  1.0f, 0.0f));
        set_vertex(3, rgm::vec3( 1.0f, -1.0f, 0.0f));

        set_normal(0, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(1, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(2, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(3, rgm::vec3(0.0f, 0.0f, 1.0f));

        set_texcoord(0, rgm::vec2(0.0f, 0.0f));
        set_texcoord(1, rgm::vec2(0.0f, 1.0f));
        set_texcoord(2, rgm::vec2(1.0f, 1.0f));
        set_texcoord(3, rgm::vec2(1.0f, 0.0f));

        set_tangent(0, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(1, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(2, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(3, rgm::vec3(1.0f, 0.0f, 0.0f));

        set_color(0, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(1, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(2, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(3, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        set_face_count(2);
        set_face(0, 0, 2, 1);
        set_face(1, 0, 3, 2);
    }


    void Mesh::create_plane(float width, float height)
    {
        float w2 = width / 2.0f;
        float h2 = height / 2.0f;

        set_vertex_count(4);

        set_vertex(0, rgm::vec3(-w2, -h2, 0.0f));
        set_vertex(1, rgm::vec3(-w2,  h2, 0.0f));
        set_vertex(2, rgm::vec3( w2,  h2, 0.0f));
        set_vertex(3, rgm::vec3( w2, -h2, 0.0f));

        set_normal(0, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(1, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(2, rgm::vec3(0.0f, 0.0f, 1.0f));
        set_normal(3, rgm::vec3(0.0f, 0.0f, 1.0f));

        set_texcoord(0, rgm::vec2(0.0f, 0.0f));
        set_texcoord(1, rgm::vec2(0.0f, 1.0f));
        set_texcoord(2, rgm::vec2(1.0f, 1.0f));
        set_texcoord(3, rgm::vec2(1.0f, 0.0f));

        set_tangent(0, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(1, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(2, rgm::vec3(1.0f, 0.0f, 0.0f));
        set_tangent(3, rgm::vec3(1.0f, 0.0f, 0.0f));

        set_color(0, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(1, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(2, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        set_color(3, rgm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        set_face_count(2);
        set_face(0, 0, 2, 1);
        set_face(1, 0, 3, 2);
    }

    void Mesh::create_box(const rgm::vec3& size)
    {
       rgm::vec3 hs = size * 0.5f;

        set_vertex_count(24);
        set_face_count(12);

        // x pos face
        set_vertex(0, rgm::vec3(hs[0], -hs[1], -hs[2]));
        set_vertex(1, rgm::vec3(hs[0],  hs[1], -hs[2]));
        set_vertex(2, rgm::vec3(hs[0],  hs[1],  hs[2]));
        set_vertex(3, rgm::vec3(hs[0], -hs[1],  hs[2]));

        set_normal(0, rgm::vec3(1, 0, 0));
        set_normal(1, rgm::vec3(1, 0, 0));
        set_normal(2, rgm::vec3(1, 0, 0));
        set_normal(3, rgm::vec3(1, 0, 0));
        
        set_texcoord(0, rgm::vec2(0, 1));
        set_texcoord(1, rgm::vec2(1, 1));
        set_texcoord(2, rgm::vec2(1, 0));
        set_texcoord(3, rgm::vec2(0, 0));
        
        set_face(0, 0, 1, 2);
        set_face(1, 0, 2, 3);
        
        // x neg
        set_vertex(4, rgm::vec3(-hs[0], -hs[1], -hs[2]));
        set_vertex(5, rgm::vec3(-hs[0],  hs[1], -hs[2]));
        set_vertex(6, rgm::vec3(-hs[0],  hs[1],  hs[2]));
        set_vertex(7, rgm::vec3(-hs[0], -hs[1],  hs[2]));

        set_normal(4, rgm::vec3(-1, 0, 0));
        set_normal(5, rgm::vec3(-1, 0, 0));
        set_normal(6, rgm::vec3(-1, 0, 0));
        set_normal(7, rgm::vec3(-1, 0, 0));


        set_texcoord(4, rgm::vec2(0, 1));
        set_texcoord(5, rgm::vec2(1, 1));
        set_texcoord(6, rgm::vec2(1, 0));
        set_texcoord(7, rgm::vec2(0, 0));
        
        set_face(2, 6, 5, 4);
        set_face(3, 7, 4, 6);
                
        // y pos
        set_vertex( 8, rgm::vec3(-hs[0], hs[1], -hs[2]));
        set_vertex( 9, rgm::vec3( hs[0], hs[1], -hs[2]));
        set_vertex(10, rgm::vec3( hs[0], hs[1],  hs[2]));
        set_vertex(11, rgm::vec3(-hs[0], hs[1],  hs[2]));

        set_normal( 8, rgm::vec3(0, 1, 0));
        set_normal( 9, rgm::vec3(0, 1, 0));
        set_normal(10, rgm::vec3(0, 1, 0));
        set_normal(11, rgm::vec3(0, 1, 0));


        set_texcoord( 8, rgm::vec2(0, 1));
        set_texcoord( 9, rgm::vec2(1, 1));
        set_texcoord(10, rgm::vec2(1, 0));
        set_texcoord(11, rgm::vec2(0, 0));
        
        set_face(4, 8, 9, 10);
        set_face(5, 8, 10, 11);

        // y neg
        set_vertex(12, rgm::vec3(-hs[0], -hs[1], -hs[2]));
        set_vertex(13, rgm::vec3( hs[0], -hs[1], -hs[2]));
        set_vertex(14, rgm::vec3( hs[0], -hs[1],  hs[2]));
        set_vertex(15, rgm::vec3(-hs[0], -hs[1],  hs[2]));

        set_normal(12, rgm::vec3(0, -1, 0));
        set_normal(13, rgm::vec3(0, -1, 0));
        set_normal(14, rgm::vec3(0, -1, 0));
        set_normal(15, rgm::vec3(0, -1, 0));

        set_texcoord(12, rgm::vec2(0, 1));
        set_texcoord(13, rgm::vec2(1, 1));
        set_texcoord(14, rgm::vec2(1, 0));
        set_texcoord(15, rgm::vec2(0, 0));
        
        set_face(6, 14, 13, 12);
        set_face(7, 15, 12, 14);
        
        // z pos
        set_vertex(16, rgm::vec3(-hs[0], -hs[1], hs[2]));
        set_vertex(17, rgm::vec3( hs[0], -hs[1], hs[2]));
        set_vertex(18, rgm::vec3( hs[0],  hs[1], hs[2]));
        set_vertex(19, rgm::vec3(-hs[0],  hs[1], hs[2]));

        set_normal(16, rgm::vec3(0, 0, 1));
        set_normal(17, rgm::vec3(0, 0, 1));
        set_normal(18, rgm::vec3(0, 0, 1));
        set_normal(19, rgm::vec3(0, 0, 1));

        set_texcoord(16, rgm::vec2(0, 1));
        set_texcoord(17, rgm::vec2(1, 1));
        set_texcoord(18, rgm::vec2(1, 0));
        set_texcoord(19, rgm::vec2(0, 0));
        
        set_face(8, 16, 17, 18);
        set_face(9, 16, 18, 19);
        
        // z neg
        set_vertex(20, rgm::vec3(-hs[0], -hs[1], -hs[2]));
        set_vertex(21, rgm::vec3( hs[0], -hs[1], -hs[2]));
        set_vertex(22, rgm::vec3( hs[0],  hs[1], -hs[2]));
        set_vertex(23, rgm::vec3(-hs[0],  hs[1], -hs[2]));

        set_normal(20, rgm::vec3(0, 0, -1));
        set_normal(21, rgm::vec3(0, 0, -1));
        set_normal(22, rgm::vec3(0, 0, -1));
        set_normal(23, rgm::vec3(0, 0, -1));

        set_texcoord(20, rgm::vec2(0, 1));
        set_texcoord(21, rgm::vec2(1, 1));
        set_texcoord(22, rgm::vec2(1, 0));
        set_texcoord(23, rgm::vec2(0, 0));
        
        set_face(10, 22, 21, 20);
        set_face(11, 23, 20, 22);
    }

    size_t Mesh::get_vertex_count() const
    {
        return vertices.size() / 3;
    }

    void Mesh::set_vertex(size_t i, const rgm::vec3& v)
    {
        size_t b = i * 4;
        vertices[b + 0] = v[0];
        vertices[b + 1] = v[1];
        vertices[b + 2] = v[2];
        vertices[b + 3] = 1.0f;
    }

   rgm::vec3 Mesh::get_vertex(size_t i) const
    {
        size_t b = i * 3;
        return rgm::vec3(vertices[b + 0], vertices[b + 1], vertices[b + 2]);
    }

    void Mesh::set_normal(size_t i, const rgm::vec3& v)
    {
        size_t b = i * 3;
        normals[b + 0] = v[0];
        normals[b + 1] = v[1];
        normals[b + 2] = v[2];
    }

   rgm::vec3 Mesh::get_normal(size_t i) const
    {
        size_t b = i * 3;
        return rgm::vec3(normals[b + 0], normals[b + 1], normals[b + 2]);
    }

    void Mesh::set_texcoord(size_t i, const rgm::vec2& v)
    {
        size_t b = i * 2;
        texcoords[b + 0] = v[0];
        texcoords[b + 1] = v[1];
    }

   rgm::vec2 Mesh::get_texcoord(size_t i) const
    {
        size_t b = i * 2;
        return rgm::vec2(texcoords[b + 0], texcoords[b + 1]);
    }

    void Mesh::set_tangent(size_t i, const rgm::vec3& v)
    {
        size_t b = i * 3;
        tangents[b + 0] = v[0];
        tangents[b + 1] = v[1];
        tangents[b + 2] = v[2];
    }

   rgm::vec3 Mesh::get_tangent(size_t i) const
    {
        size_t b = i * 3;
        return rgm::vec3(tangents[b + 0], tangents[b + 1], tangents[b + 2]);
    }

    void Mesh::set_color(size_t i, const rgm::vec4& v)
    {
        size_t ba = i * 4;
        colors[ba + 0] = v[0];
        colors[ba + 1] = v[1];
        colors[ba + 2] = v[2];
        colors[ba + 3] = v[3];
    }

   rgm::vec4 Mesh::get_color(size_t i) const
    {
        size_t b = i * 4;
        return rgm::vec4(colors[b + 0], colors[b + 1], colors[b + 2], colors[b + 3]);
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
        glBufferData(GL_ARRAY_BUFFER, vcount * 4 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(VERTEX_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(NORMAL_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 2 * sizeof(float), &texcoords[0], GL_STATIC_DRAW);
        glVertexAttribPointer(TEXCOORD_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(TEXCOORD_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[TANGENT_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), &tangents[0], GL_STATIC_DRAW);
        glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(TANGENT_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[COLOR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, vcount * 4 * sizeof(float), &colors[0], GL_STATIC_DRAW);
        glVertexAttribPointer(COLOR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOR_BUFFER);

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

    void Mesh::draw() const
    {
        if (vao == 0)
        {
            const_cast<Mesh*>(this)->upload();
        }

        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    
    std::shared_ptr<Mesh> load_mesh(const std::string& file)
    {
        std::shared_ptr<Mesh> mesh(new Mesh);
        mesh->load(file);
        return mesh;
    }
}
