/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef _PKZO_MESH_H_
#define _PKZO_MESH_H_

#include <tuple>
#include <vector>
#include <memory>
#include <rgm/rgm.h>

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Mesh
    {
    public:
        
        Mesh();

        Mesh(const Mesh&) = delete;

        ~Mesh();

        const Mesh& operator = (const Mesh&) = delete;

        void load(const std::string& file);

        void create_plane(float width, float height);

        void create_screen_plane();

        void create_box(const rgm::vec3& size);

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

        void set_color(size_t i, const rgm::vec4& c);

       rgm::vec4 get_color(size_t i) const;

        void set_face_count(size_t value);

        size_t get_face_count() const;


        void set_face(size_t i, unsigned int a, unsigned int b, unsigned int c);

        void add_face(unsigned int a, unsigned int b, unsigned int c);

        std::tuple<unsigned int, unsigned int, unsigned int> get_face(size_t i) const;

        // void compute_normals();

        // void compute_tangents();

        void upload();

        void release();

        void draw() const;

    private:
        std::vector<float> vertices;  // v4f
        std::vector<float> normals;   // v3f
        std::vector<float> texcoords; // v2f
        std::vector<float> tangents;  // v3f
        std::vector<float> colors;    // v4f

        std::vector<unsigned int> faces;       // v3i

        unsigned int vao;
        unsigned int buffers[6];
    };

    PKZO_EXPORT 
    std::shared_ptr<Mesh> load_mesh(const std::string& file);
            

}

#endif

 
