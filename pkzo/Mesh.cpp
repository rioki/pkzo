//
// pkzo
// 
// Copyright (c) 2014-2017 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "Mesh.h"

#include <cassert>
#include <map>

#include "path.h"
#include "strex.h"

#include "PlyParser.h"
#include "ObjParser.h"

namespace pkzo
{
    Mesh::Mesh()
    : min(0), max(0) {}

    Mesh::Mesh(const std::string& file)
    : Mesh()
    {
        std::string ext = path::ext(file);
        switch (strex::hash(ext))
        {
        case strex::hash("ply"):
            load_ply(file);
            break;
        case strex::hash("obj"):
            load_obj(file);
            break;
        default:
            throw std::runtime_error("Unknown mesh extention.");
        }

        if (normals.empty() || normals[0] == rgm::vec3(0))
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

    void Mesh::set_vertex(size_t i, const rgm::vec3& v)
    {  
        min = rgm::min(min, v);
        max = rgm::max(max, v);
        vertices.at(i) = v;        
    }

    rgm::vec3 Mesh::get_vertex(size_t i) const
    {
        return vertices.at(i);
    }

    void Mesh::set_normal(size_t i, const rgm::vec3& v)
    {
        normals.at(i) = v;
    }

    rgm::vec3 Mesh::get_normal(size_t i) const
    {
        return normals.at(i);
    }

    void Mesh::set_texcoord(size_t i, const rgm::vec2& v)
    {
        texcoords.at(i) = v;
    }

    rgm::vec2 Mesh::get_texcoord(size_t i) const
    {
        return texcoords.at(i);
    }

    void Mesh::set_tangent(size_t i, const rgm::vec3& v)
    {
        tangents.at(i) = v;
    }

    rgm::vec3 Mesh::get_tangent(size_t i) const
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
        faces.at(i) = rgm::uvec3(a, b, c);  
    }

    void Mesh::add_face(unsigned int a, unsigned int b, unsigned int c)
    {
        faces.push_back(rgm::uvec3(a, b, c));         
    }

    rgm::uvec3 Mesh::get_face(size_t i) const
    {
        return faces.at(i);
    }

    void Mesh::compute_normals()
    {
        normals.resize(vertices.size(), rgm::vec3(0));

        for (size_t i = 0; i < faces.size(); i++)
        {
            unsigned int ia = faces[i][0];
            unsigned int ib = faces[i][1];
            unsigned int ic = faces[i][2];

            rgm::vec3 e1 = vertices[ia] - vertices[ib];
            rgm::vec3 e2 = vertices[ia] - vertices[ic];
            rgm::vec3 no = rgm::cross(e1, e2);

            normals[ia] += no;
            normals[ib] += no;
            normals[ic] += no;
        }

        for (size_t i = 0; i < normals.size(); i++)
        {
            normals[i] = rgm::normalize(normals[i]);
        }
    }

    void Mesh::compute_tangents()
    {
        std::vector<rgm::vec3> tan1(get_vertex_count(), rgm::vec3(0));
        std::vector<rgm::vec3> tan2(get_vertex_count(), rgm::vec3(0));
        
        for (size_t i = 0; i < faces.size(); i++)
        {
            rgm::vec3 v1 = vertices[faces[i][0]];
            rgm::vec3 v2 = vertices[faces[i][1]];
            rgm::vec3 v3 = vertices[faces[i][2]];
            
            rgm::vec2 w1 = get_texcoord(faces[i][0]);
            rgm::vec2 w2 = get_texcoord(faces[i][1]);
            rgm::vec2 w3 = get_texcoord(faces[i][2]);
            
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
            rgm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
            rgm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);
            
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
            rgm::vec3& n  = normals[i];
            rgm::vec3& t1 = tan1[i];
            rgm::vec3& t2 = tan2[i];
            
            rgm::vec3 t = rgm::normalize(t1 - n * rgm::dot(n, t1));
            if (rgm::dot(rgm::cross(n, t1), t2) < 0.0f) 
            {
                tangents[i] = -t;
            }
            else
            {
                tangents[i] = t;
            }            
        }
    }
    
    std::tuple<rgm::vec3, rgm::vec3> Mesh::get_bounds() const
    {
        return std::make_tuple(min, max);
    }

    std::tuple<rgm::vec3, float> Mesh::get_bounding_sphere() const
    {
        auto center = (min + max) / 2.0f;
        auto radius = rgm::length(max - center);
        return std::make_tuple(center, radius);
    }

    const std::vector<rgm::vec3>& Mesh::get_vertices() const
    {
        return vertices;
    }

    const std::vector<rgm::vec3>& Mesh::get_normals() const
    {
        return normals;
    }

    const std::vector<rgm::vec2>& Mesh::get_texcoords() const
    {
        return texcoords;
    }

    const std::vector<rgm::vec3>& Mesh::get_tangents() const
    {
        return tangents;
    }

    const std::vector<rgm::uvec3>& Mesh::get_faces() const
    {
        return faces;
    }

    void Mesh::load_ply(const std::string& file)
    {
        PlyParser parser;
        parser.parse(file);

        vertices  = parser.get_vertices(); 
        normals   = parser.get_normals();  
        texcoords = parser.get_texcoords();

        for (rgm::vec3 v : vertices)
        {
            min = rgm::min(min, v);
            max = rgm::max(max, v);
        }

        auto fs = parser.get_indexes(); 
        faces.resize(fs.size());
        for (size_t i = 0; i < fs.size(); i++)
        {
            faces[i] = rgm::uvec3(fs[i][0], fs[i][1], fs[i][2]);  
        } 
    }

    struct iv3less
    {
        bool operator () (const rgm::ivec3& a, const rgm::ivec3& b) const 
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

    void Mesh::load_obj(const std::string& file)
    {
        ObjParser parser;
        parser.parse(file);

        auto v = parser.get_vertices(); 
        auto n = parser.get_normals();  
        auto t = parser.get_texcoords();

        auto f = parser.get_faces();
        
        vertices.clear();
        normals.clear();
        texcoords.clear();

        
        std::map<rgm::ivec3, size_t, iv3less> index_mapping;

        for (auto face : f)
        {
            std::vector<size_t> idx;

            for (rgm::ivec3 fv : face)
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

                    rgm::vec2 tc = t[fv[1] - 1];
                    tc[1] = 1 - tc[1];
                    texcoords.push_back(tc);
                                        
                    index_mapping[fv] = vi;
                    idx.push_back(vi);
                }
            }   

            for (unsigned int i = 2; i < idx.size(); i++)
            {
                add_face(idx[0], idx[i - 1], idx[i]);
            }
        }

        for (rgm::vec3 v : vertices)
        {
            min = rgm::min(min, v);
            max = rgm::max(max, v);
        }
    }
}
