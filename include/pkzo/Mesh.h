//
// pkzo
// 
// Copyright 2015 Sean Farrell
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

#include <tuple>
#include <vector>

#include "defines.h"

namespace pkzo
{
    class Shader;

    /**
     * Triangle Mesh
     *
     * @todo compute_normals
     * @todo compute_tangents
     * @todo apply_white
     **/
    class PKZO_EXPORT Mesh
    {
    public:
        
        /**
         * Contruct a Triangle Mesh
         **/
        Mesh();

        Mesh(const Mesh&) = delete;

        /**
         * Destroy a Triangle Mesh
         **/
        ~Mesh();

        const Mesh& operator = (const Mesh&) = delete;

        /**
         * Load a Triangle Mesh from File
         *
         * This function loads a tiangle mesh from file. Currently
         * only the PLY format is supported.
         * 
         * @param file the file to load from, relative to the working directory
         **/
        void load(const std::string& file);

        /**
         * Create a 2D Plane
         *
         * This function create a mesh representing a 2D plane in the xy plane
         * with the origin at the center.
         * 
         * @param width  the width of the plane
         * @param height the height of the plane
         **/
        void create_plane(float width, float height);

        /**
         * Set the Vertex Count
         * 
         * This functions sets the vertex count and resizes all vertex buffers.
         *
         * @param value the size to set
         **/
        void set_vertex_count(size_t value);

        /**
         * Get the Vertex Count
         * 
         * @returns the number of vertexes
         **/
        size_t get_vertex_count() const;

        /**
         * Set a Vertex
         *
         * @param i the index of the vertex
         * @param x the x value of the vertex
         * @param y the y value of the vertex
         * @param z the z value of the vertex
         **/
        void set_vertex(size_t i, float x, float y, float z);

        /**
         * Get a Vertex
         * 
         * @param i the index of the vertex
         *
         * @returns a tuple containing the x, y and z component of the vertex
         **/
        std::tuple<float, float, float> get_vertex(size_t i) const;

        /**
         * Set a Normal
         *
         * @param i the index of the normal
         * @param x the x value of the normal
         * @param y the y value of the normal
         * @param z the z value of the normal
         **/
        void set_normal(size_t i, float x, float y, float z);

        /**
         * Get a Normal
         * 
         * @param i the index of the normal
         *
         * @returns a tuple containing the x, y and z component of the normal
         **/
        std::tuple<float, float, float> get_normal(size_t i) const;

        /**
         * Set a Texture Coordinate
         *
         * @param i the index of the texture coordinate
         * @param u the u value of the texture coordinate
         * @param v the v value of the texture coordinate
         **/
        void set_texcoord(size_t i, float u, float v);

        /**
         * Get a Texture Coordinate
         * 
         * @param i the index of the texture coordinate
         *
         * @returns a tuple containing the u and v component of the texture coordinate
         **/
        std::tuple<float, float> get_texcoord(size_t i) const;

        /**
         * Set a Tangent
         *
         * @param i the index of the tangent
         * @param x the x value of the tangent
         * @param y the y value of the tangent
         * @param z the z value of the tangent
         **/
        void set_tangent(size_t i, float x, float y, float z);

        /**
         * Get a Tangent
         * 
         * @param i the index of the tangent
         *
         * @returns a tuple containing the x, y and z component of the tangent
         **/
        std::tuple<float, float, float> get_tangent(size_t i) const;

        /**
         * Set a Vertex Color
         *
         * @param i the index of the vertex color
         * @param r the red value of the vertex color
         * @param g the green value of the vertex color
         * @param b the blue value of the vertex color
         * @param a the alpha value of the vertex color
         **/
        void set_color(size_t i, float r, float g, float b, float a);

        /**
         * Get a Vertex Color
         * 
         * @param i the index of the vertex color
         *
         * @returns a tuple containing the r, g, b and a component of the vertex color
         **/
        std::tuple<float, float, float, float> get_color(size_t i) const;

        /**
         * Set the Number of Triangles
         *
         * This function sets the number of triangles in this mesh 
         * and resizes the index buffer.
         * 
         * @param value the number of trangles
         **/
        void set_face_count(size_t value);

        /**
         * Get the Number of Triangles
         *
         * @returns number of triangles
         **/
        size_t get_face_count() const;

        /**
         * Set a Face
         * 
         * @param i the index of the face
         * @param a the first index 
         * @param b the second index 
         * @param c the third index
         **/
        void set_face(size_t i, unsigned int a, unsigned int b, unsigned int c);

        /**
         * Adds a Face
         * 
         * @param a the first index 
         * @param b the second index 
         * @param c the third index
         **/
        void add_face(unsigned int a, unsigned int b, unsigned int c);

        /**
         * Get a Face
         *
         * @param i the index of the face
         *
         * @returns a tuple conainting a, b and c indexes
         **/
        std::tuple<unsigned int, unsigned int, unsigned int> get_face(size_t i) const;

        // void compute_normals();

        // void compute_tangents();

        /**
         * Upload to Video Memory
         *
         * This function compiles and uploads the geometry to video memory. 
         * 
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void upload();

        /**
         * Release from Video Memory
         *
         * This function will instruct the video memory to release the geometry.
         * 
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void release();

        /**
         * Draw a Mesh
         *
         * This function will bind the attributes vec3 aVertex, vec3 aNormal, vec2 aTexCoord, vec3 aTangent
         * and vec4 aColor and submit the indexes for rendering. 
         * 
         * @param shader a valid, bound and configured GLSL shader program
         *
         * @warning This function can only be called with a valid and active OpenGL context. 
         **/
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

 
