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

#ifndef _PKZO_MESH_H_
#define _PKZO_MESH_H_

#include <memory>
#include <vector>
#include <tuple>
#include <rgm/rgm.h>
#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Mesh
    {
    public:
        
        Mesh();

        Mesh(const std::string& file);

        Mesh(const Mesh&) = delete;

        ~Mesh();

        const Mesh& operator = (const Mesh&) = delete;

        void set_vertex_count(size_t value);

        size_t get_vertex_count() const;

        void set_vertex(size_t i, const rgm::vec3& v);

        rgm::vec3 get_vertex(size_t i) const;

        void set_normal(size_t i, const rgm::vec3& v);

        rgm::vec3 get_normal(size_t i) const;

        void set_texcoord(size_t i, const rgm::vec2& v);

        rgm::vec2 get_texcoord(size_t i) const;

        void set_tangent(size_t i, const rgm::vec3& v);

        rgm::vec3 get_tangent(size_t i) const;

        void set_face_count(size_t value);

        size_t get_face_count() const;

        void set_face(size_t i, unsigned int a, unsigned int b, unsigned int c);

        void add_face(unsigned int a, unsigned int b, unsigned int c);

        rgm::uvec3 get_face(size_t i) const;

        void compute_normals();

        void compute_tangents();

        std::tuple<rgm::vec3, rgm::vec3> get_bounds() const;

        std::tuple<rgm::vec3, float> get_bounding_sphere() const;

        const std::vector<rgm::vec3>& get_vertices() const;

        const std::vector<rgm::vec3>& get_normals() const;

        const std::vector<rgm::vec2>& get_texcoords() const;

        const std::vector<rgm::vec3>& get_tangents() const;

        const std::vector<rgm::uvec3>& get_faces() const;

    private:
        rgm::vec3 min;
        rgm::vec3 max;

        std::vector<rgm::vec3> vertices;  
        std::vector<rgm::vec3> normals;   
        std::vector<rgm::vec2> texcoords; 
        std::vector<rgm::vec3> tangents; 
        
        std::vector<rgm::uvec3> faces;

        void load_ply(const std::string& file);
        void load_obj(const std::string& file);
    };
}

#endif

 
