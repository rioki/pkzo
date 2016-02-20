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

#ifndef _PKZO_SCENE_RENDERER_H_
#define _PKZO_SCENE_RENDERER_H_

#include <list>

#include <rgm/rgm.h>

#include <pkzo/defines.h>
#include <pkzo/Shader.h>

namespace pkzo
{
    using namespace rgm;

    class Mesh;
    class Material;

    class PKZO_EXPORT SceneRenderer
    {
    public:
        SceneRenderer();

        SceneRenderer(const SceneRenderer&) = delete;

        ~SceneRenderer();

        const SceneRenderer& operator = (const SceneRenderer&) = delete;

        void orient_camera(const mat4& projection, const mat4& view);

        void queue_ambient_light(const vec3& color);

        void queue_directional_light(const vec3& direction, const vec3& color);

        void queue_point_light(const vec3& position, const vec3& color, float range);

        void queue_spot_light(const vec3& position, const vec3& direction, const vec3& color, float range, float angle);

        void queue_geometry(mat4 transform, const Mesh& mesh, Material& material);

        void render();

    private:
        enum LightType 
        {
            AMBIENT_LIGHT,
            DIRECTIONAL_LIGHT,
            POINT_LIGHT,
            SPOT_LIGHT
        };

        struct LightInfo
        {
            LightType type;
            vec3      direction;
            vec3      position;
            float     range;
            float     angle;
            vec3      color;
        };

        struct GeometryInfo
        {
            mat4            transform;
            const Mesh*     mesh;
            const Material* material;
        };

        mat4                    projection_matrix;
        mat4                    view_matrix;
        std::list<LightInfo>    lights;
        std::list<GeometryInfo> geometries;

        // TMP phong for test purposes
        Shader phong_shader;
    };
}

#endif
