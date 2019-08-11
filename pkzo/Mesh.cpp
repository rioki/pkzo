// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Mesh.h"

#include <cassert>
#include <map>
#include <stdexcept>
#include <GL/glew.h>

#include "dbg.h"
#include "stdex.h"
#include "Shader.h"
#include "PlyParser.h"
#include "ObjParser.h"

namespace pkzo
{
    std::shared_ptr<Mesh> Mesh::create_rectangle(glm::vec2 size, bool flip_y_uv)
    {
        auto hs = size * 0.5f;

        auto mesh = std::make_shared<Mesh>();
        mesh->set_vertex_count(4u);

        mesh->set_vertex(0u, glm::vec3( hs[0],  hs[1], 0.0f));
        mesh->set_vertex(1u, glm::vec3( hs[0], -hs[0], 0.0f));
        mesh->set_vertex(2u, glm::vec3(-hs[0], -hs[0], 0.0f));
        mesh->set_vertex(3u, glm::vec3(-hs[0],  hs[0], 0.0f));

        mesh->set_normal(0u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(1u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(2u, glm::vec3(0.0f, 0.0f, 1.0f));
        mesh->set_normal(3u, glm::vec3(0.0f, 0.0f, 1.0f));

        if (flip_y_uv)
        {
            mesh->set_texcoord(0u, glm::vec2(1.0f, 0.0f));
            mesh->set_texcoord(1u, glm::vec2(1.0f, 1.0f));
            mesh->set_texcoord(2u, glm::vec2(0.0f, 1.0f));
            mesh->set_texcoord(3u, glm::vec2(0.0f, 0.0f));
        }
        else
        {
            mesh->set_texcoord(0u, glm::vec2(1.0f, 1.0f));
            mesh->set_texcoord(1u, glm::vec2(1.0f, 0.0f));
            mesh->set_texcoord(2u, glm::vec2(0.0f, 0.0f));
            mesh->set_texcoord(3u, glm::vec2(0.0f, 1.0f));
        }

        mesh->set_tangent(0u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(1u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(2u, glm::vec3(1.0f, 0.0f, 0.0f));
        mesh->set_tangent(3u, glm::vec3(1.0f, 0.0f, 0.0f));

        mesh->set_face_count(2u);
        mesh->set_face(0u, 0u, 1u, 2u);
        mesh->set_face(1u, 2u, 3u, 0u);

        return mesh;
    }

    // TODO tangents
    std::shared_ptr<Mesh> Mesh::create_box(glm::vec3 size)
    {
        auto hs = size * 0.5f;

        auto mesh = std::make_shared<Mesh>();
        mesh->set_vertex_count(24);
        mesh->set_face_count(12);

        // x pos face
        mesh->set_vertex(0, glm::vec3(hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(1, glm::vec3(hs[0],  hs[1], -hs[2]));
        mesh->set_vertex(2, glm::vec3(hs[0],  hs[1],  hs[2]));
        mesh->set_vertex(3, glm::vec3(hs[0], -hs[1],  hs[2]));

        mesh->set_normal(0, glm::vec3(1, 0, 0));
        mesh->set_normal(1, glm::vec3(1, 0, 0));
        mesh->set_normal(2, glm::vec3(1, 0, 0));
        mesh->set_normal(3, glm::vec3(1, 0, 0));

        mesh->set_texcoord(0, glm::vec2(0, 1));
        mesh->set_texcoord(1, glm::vec2(1, 1));
        mesh->set_texcoord(2, glm::vec2(1, 0));
        mesh->set_texcoord(3, glm::vec2(0, 0));

        mesh->set_face(0, 0, 1, 2);
        mesh->set_face(1, 0, 2, 3);

        // x neg
        mesh->set_vertex(4, glm::vec3(-hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(5, glm::vec3(-hs[0],  hs[1], -hs[2]));
        mesh->set_vertex(6, glm::vec3(-hs[0],  hs[1],  hs[2]));
        mesh->set_vertex(7, glm::vec3(-hs[0], -hs[1],  hs[2]));

        mesh->set_normal(4, glm::vec3(-1, 0, 0));
        mesh->set_normal(5, glm::vec3(-1, 0, 0));
        mesh->set_normal(6, glm::vec3(-1, 0, 0));
        mesh->set_normal(7, glm::vec3(-1, 0, 0));


        mesh->set_texcoord(4, glm::vec2(0, 1));
        mesh->set_texcoord(5, glm::vec2(1, 1));
        mesh->set_texcoord(6, glm::vec2(1, 0));
        mesh->set_texcoord(7, glm::vec2(0, 0));

        mesh->set_face(2, 6, 5, 4);
        mesh->set_face(3, 7, 4, 6);

        // y pos
        mesh->set_vertex( 8, glm::vec3(-hs[0], hs[1], -hs[2]));
        mesh->set_vertex( 9, glm::vec3( hs[0], hs[1], -hs[2]));
        mesh->set_vertex(10, glm::vec3( hs[0], hs[1],  hs[2]));
        mesh->set_vertex(11, glm::vec3(-hs[0], hs[1],  hs[2]));

        mesh->set_normal( 8, glm::vec3(0, 1, 0));
        mesh->set_normal( 9, glm::vec3(0, 1, 0));
        mesh->set_normal(10, glm::vec3(0, 1, 0));
        mesh->set_normal(11, glm::vec3(0, 1, 0));


        mesh->set_texcoord( 8, glm::vec2(0, 1));
        mesh->set_texcoord( 9, glm::vec2(1, 1));
        mesh->set_texcoord(10, glm::vec2(1, 0));
        mesh->set_texcoord(11, glm::vec2(0, 0));

        mesh->set_face(4, 8, 9, 10);
        mesh->set_face(5, 8, 10, 11);

        // y neg
        mesh->set_vertex(12, glm::vec3(-hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(13, glm::vec3( hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(14, glm::vec3( hs[0], -hs[1],  hs[2]));
        mesh->set_vertex(15, glm::vec3(-hs[0], -hs[1],  hs[2]));

        mesh->set_normal(12, glm::vec3(0, -1, 0));
        mesh->set_normal(13, glm::vec3(0, -1, 0));
        mesh->set_normal(14, glm::vec3(0, -1, 0));
        mesh->set_normal(15, glm::vec3(0, -1, 0));

        mesh->set_texcoord(12, glm::vec2(0, 1));
        mesh->set_texcoord(13, glm::vec2(1, 1));
        mesh->set_texcoord(14, glm::vec2(1, 0));
        mesh->set_texcoord(15, glm::vec2(0, 0));

        mesh->set_face(6, 14, 13, 12);
        mesh->set_face(7, 15, 12, 14);

        // z pos
        mesh->set_vertex(16, glm::vec3(-hs[0], -hs[1], hs[2]));
        mesh->set_vertex(17, glm::vec3( hs[0], -hs[1], hs[2]));
        mesh->set_vertex(18, glm::vec3( hs[0],  hs[1], hs[2]));
        mesh->set_vertex(19, glm::vec3(-hs[0],  hs[1], hs[2]));

        mesh->set_normal(16, glm::vec3(0, 0, 1));
        mesh->set_normal(17, glm::vec3(0, 0, 1));
        mesh->set_normal(18, glm::vec3(0, 0, 1));
        mesh->set_normal(19, glm::vec3(0, 0, 1));

        mesh->set_texcoord(16, glm::vec2(0, 1));
        mesh->set_texcoord(17, glm::vec2(1, 1));
        mesh->set_texcoord(18, glm::vec2(1, 0));
        mesh->set_texcoord(19, glm::vec2(0, 0));

        mesh->set_face(8, 16, 17, 18);
        mesh->set_face(9, 16, 18, 19);

        // z neg
        mesh->set_vertex(20, glm::vec3(-hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(21, glm::vec3( hs[0], -hs[1], -hs[2]));
        mesh->set_vertex(22, glm::vec3( hs[0],  hs[1], -hs[2]));
        mesh->set_vertex(23, glm::vec3(-hs[0],  hs[1], -hs[2]));

        mesh->set_normal(20, glm::vec3(0, 0, -1));
        mesh->set_normal(21, glm::vec3(0, 0, -1));
        mesh->set_normal(22, glm::vec3(0, 0, -1));
        mesh->set_normal(23, glm::vec3(0, 0, -1));

        mesh->set_texcoord(20, glm::vec2(0, 1));
        mesh->set_texcoord(21, glm::vec2(1, 1));
        mesh->set_texcoord(22, glm::vec2(1, 0));
        mesh->set_texcoord(23, glm::vec2(0, 0));

        mesh->set_face(10, 22, 21, 20);
        mesh->set_face(11, 23, 20, 22);

        return mesh;
    }

    std::shared_ptr<Mesh> Mesh::create_fullscreen_rectangle()
    {
        return Mesh::create_rectangle(glm::uvec2(2.0f));
    }

    Mesh::Mesh()
    : min(0), max(0) {}

    Mesh::Mesh(const fs::path& file)
    : Mesh()
    {
        switch (stdex::hash(file.extension().string()))
        {
        case stdex::hash(".ply"):
            load_ply(file);
            break;
        case stdex::hash(".obj"):
            load_obj(file);
            break;
        default:
            throw std::runtime_error("Unknown mesh extention.");
        }

        if (normals.empty() || normals[0] == glm::vec3(0))
        {
            compute_normals();
        }

        compute_tangents();
    }

    Mesh::~Mesh() {}

    void Mesh::set_vertex_count(size_t value)
    {
        vertices.resize(value);
        normals.resize(value);
        texcoords.resize(value);
        tangents.resize(value);
    }

    size_t Mesh::get_vertex_count() const
    {
        return vertices.size();
    }

    void Mesh::set_vertex(size_t i, const glm::vec3& v)
    {
        min = glm::min(min, v);
        max = glm::max(max, v);
        vertices.at(i) = v;
    }

    glm::vec3 Mesh::get_vertex(size_t i) const
    {
        return vertices.at(i);
    }

    void Mesh::set_normal(size_t i, const glm::vec3& v)
    {
        normals.at(i) = v;
    }

    glm::vec3 Mesh::get_normal(size_t i) const
    {
        return normals.at(i);
    }

    void Mesh::set_texcoord(size_t i, const glm::vec2& v)
    {
        texcoords.at(i) = v;
    }

    glm::vec2 Mesh::get_texcoord(size_t i) const
    {
        return texcoords.at(i);
    }

    void Mesh::set_tangent(size_t i, const glm::vec3& v)
    {
        tangents.at(i) = v;
    }

    glm::vec3 Mesh::get_tangent(size_t i) const
    {
        return tangents.at(i);
    }

    void Mesh::set_face_count(size_t value)
    {
        faces.resize(value);
    }

    size_t Mesh::get_face_count() const
    {
        return faces.size();
    }

    void Mesh::set_face(size_t i, unsigned int a, unsigned int b, unsigned int c)
    {
        faces.at(i) = glm::uvec3(a, b, c);
    }

    void Mesh::add_face(unsigned int a, unsigned int b, unsigned int c)
    {
        faces.push_back(glm::uvec3(a, b, c));
    }

    glm::uvec3 Mesh::get_face(size_t i) const
    {
        return faces.at(i);
    }

    void Mesh::set_line_count(size_t value)
    {
        lines.resize(value);
    }

    size_t Mesh::get_line_count() const
    {
        return lines.size();
    }

    void Mesh::set_line(size_t i, const glm::uvec2& value)
    {
        lines.at(i) = value;
    }

    glm::uvec2 Mesh::get_line(size_t i) const
    {
        return lines.at(i);
    }

    void Mesh::compute_normals()
    {
        normals.resize(vertices.size(), glm::vec3(0));

        for (size_t i = 0; i < faces.size(); i++)
        {
            unsigned int ia = faces[i][0];
            unsigned int ib = faces[i][1];
            unsigned int ic = faces[i][2];

            glm::vec3 e1 = vertices[ia] - vertices[ib];
            glm::vec3 e2 = vertices[ia] - vertices[ic];
            glm::vec3 no = glm::cross(e1, e2);

            normals[ia] += no;
            normals[ib] += no;
            normals[ic] += no;
        }

        for (size_t i = 0; i < normals.size(); i++)
        {
            normals[i] = glm::normalize(normals[i]);
        }
    }

    void Mesh::compute_tangents()
    {
        std::vector<glm::vec3> tan1(get_vertex_count(), glm::vec3(0));
        std::vector<glm::vec3> tan2(get_vertex_count(), glm::vec3(0));

        for (size_t i = 0; i < faces.size(); i++)
        {
            glm::vec3 v1 = vertices[faces[i][0]];
            glm::vec3 v2 = vertices[faces[i][1]];
            glm::vec3 v3 = vertices[faces[i][2]];

            glm::vec2 w1 = get_texcoord(faces[i][0]);
            glm::vec2 w2 = get_texcoord(faces[i][1]);
            glm::vec2 w3 = get_texcoord(faces[i][2]);

            float x1 = v2[0] - v1[0];
            float x2 = v3[0] - v1[0];
            float y1 = v2[1] - v1[1];
            float y2 = v3[1] - v1[1];
            float z1 = v2[2] - v1[2];
            float z2 = v3[2] - v1[2];

            float s1 = w2[0] - w1[0];
            float s2 = w3[0] - w1[0];
            float t1 = w2[1] - w1[1];
            float t2 = w3[1] - w1[1];

            float r = 1.0F / (s1 * t2 - s2 * t1);
            glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
            glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

            tan1[faces[i][0]] += sdir;
            tan1[faces[i][1]] += sdir;
            tan1[faces[i][2]] += sdir;

            tan2[faces[i][0]] += tdir;
            tan2[faces[i][1]] += tdir;
            tan2[faces[i][2]] += tdir;
        }

        tangents.resize(vertices.size());
        for (size_t i = 0; i < get_vertex_count(); i++)
        {
            glm::vec3& n  = normals[i];
            glm::vec3& t1 = tan1[i];
            glm::vec3& t2 = tan2[i];

            glm::vec3 t = glm::normalize(t1 - n * glm::dot(n, t1));
            if (glm::dot(glm::cross(n, t1), t2) < 0.0f)
            {
                tangents[i] = -t;
            }
            else
            {
                tangents[i] = t;
            }
        }
    }

    std::tuple<glm::vec3, glm::vec3> Mesh::get_bounds() const
    {
        return std::make_tuple(min, max);
    }

    std::tuple<glm::vec3, float> Mesh::get_bounding_sphere() const
    {
        auto center = (min + max) / 2.0f;
        auto radius = glm::length(max - center);
        return std::make_tuple(center, radius);
    }

    void Mesh::load_ply(const fs::path& file)
    {
        PlyParser parser;
        parser.parse(file.string());

        vertices  = parser.get_vertices();
        normals   = parser.get_normals();
        texcoords = parser.get_texcoords();

        for (auto& v : vertices)
        {
            min = glm::min(min, v);
            max = glm::max(max, v);
        }

        auto fs = parser.get_indexes();
        faces.resize(fs.size());
        for (size_t i = 0; i < fs.size(); i++)
        {
            faces[i] = glm::uvec3(fs[i][0], fs[i][1], fs[i][2]);
        }
    }

    struct iv3less
    {
        bool operator () (const glm::ivec3& a, const glm::ivec3& b) const
        {
            if (a[0] == b[0])
            {
                if (a[1] == b[1])
                {
                    return a[2] < b[2];
                }
                else
                {
                    return a[1] < b[1];
                }
            }
            else
            {
                return a[0] < b[0];
            }
        }
    };

    void Mesh::load_obj(const fs::path& file)
    {
        ObjParser parser;
        parser.parse(file.string());

        auto v = parser.get_vertices();
        auto n = parser.get_normals();
        auto t = parser.get_texcoords();

        auto f = parser.get_faces();

        vertices.clear();
        normals.clear();
        texcoords.clear();


        std::map<glm::ivec3, size_t, iv3less> index_mapping;

        for (auto face : f)
        {
            std::vector<size_t> idx;

            for (glm::ivec3 fv : face)
            {
                auto i = index_mapping.find(fv);
                if (i != index_mapping.end())
                {
                    idx.push_back(i->second);
                }
                else
                {
                    size_t vi = vertices.size();

                    vertices.push_back(v[fv[0] - 1]);
                    normals.push_back(n[fv[2] - 1]);

                    glm::vec2 tc = t[fv[1] - 1];
                    tc[1] = 1 - tc[1];
                    texcoords.push_back(tc);

                    index_mapping[fv] = vi;
                    idx.push_back(vi);
                }
            }

            for (auto i = 2u; i < idx.size(); i++)
            {
                add_face(idx[0], idx[i - 1], idx[i]);
            }
        }

        for (glm::vec3 v : vertices)
        {
            min = glm::min(min, v);
            max = glm::max(max, v);
        }
    }

    template <typename vec>
    void bind_buffer(glm::uint buffer_id, Shader& shader, const std::string_view attribute_id)
    {
        auto adr = shader.get_attribute(attribute_id);
        if (adr != -1)
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
            glVertexAttribPointer(adr, vec::length(), GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(adr);
            PKZO_CHECK_OPENGL(glGetError());
        }
    }

    void Mesh::bind(Shader& shader)
    {
        if (vao == 0)
        {
            upload();
        }

        glBindVertexArray(vao);
        bound = true;

        bind_buffer<glm::vec3>(vertex_buffer,   shader, "pkzo_Vertex");
        bind_buffer<glm::vec3>(normal_buffer,   shader, "pkzo_Normal");
        bind_buffer<glm::vec2>(texcoord_buffer, shader, "pkzo_TexCoord");
        bind_buffer<glm::vec3>(tangent_buffer,  shader, "pkzo_Tangent");
    }

    void Mesh::unbind()
    {
        glBindVertexArray(0);
        bound = false;
        PKZO_CHECK_OPENGL(glGetError());
    }

    void Mesh::draw()
    {
        PKZO_ASSERT(bound);

        if (!faces.empty())
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(faces.size() * 3), GL_UNSIGNED_INT, 0);
        }

        if (!lines.empty())
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, line_buffer);
            glDrawElements(GL_LINES, static_cast<GLsizei>(lines.size() * 2), GL_UNSIGNED_INT, 0);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        PKZO_CHECK_OPENGL(glGetError());
    }

    template <typename vec>
    glm::uint upload_values(GLenum buffer_type, const std::vector<vec>& values)
    {
        auto glid = 0u;
        glGenBuffers(1, &glid);
        glBindBuffer(buffer_type, glid);
        glBufferData(buffer_type, values.size() * sizeof(vec), values.data(), GL_STATIC_DRAW);
        glBindBuffer(buffer_type, 0);
        PKZO_CHECK_OPENGL(glGetError());

        return glid;
    }

    void Mesh::upload()
    {
        glGenVertexArrays(1, &vao);
        PKZO_CHECK_OPENGL(glGetError());

        vertex_buffer   = upload_values(GL_ARRAY_BUFFER, vertices);
        normal_buffer   = upload_values(GL_ARRAY_BUFFER, normals);
        texcoord_buffer = upload_values(GL_ARRAY_BUFFER, texcoords);
        tangent_buffer  = upload_values(GL_ARRAY_BUFFER, tangents);

        if (!faces.empty())
        {
            face_buffer = upload_values(GL_ELEMENT_ARRAY_BUFFER, faces);
        }
        if (!lines.empty())
        {
            line_buffer = upload_values(GL_ELEMENT_ARRAY_BUFFER, lines);
        }
    }
}
