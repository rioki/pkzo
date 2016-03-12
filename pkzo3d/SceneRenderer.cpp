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

#include "SceneRenderer.h"

#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#else
// TODO ezrc
#endif

#include <GL/glew.h>
#include <pkzo/Mesh.h>

#include "Material.h"

namespace pkzo
{
    std::string LoadTextResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType)
    {
        HRSRC   hPhongVertex  = FindResource(hModule, lpName, lpType);
        HGLOBAL hgPhongVertex = LoadResource(hModule, hPhongVertex);
        DWORD   nSize         = SizeofResource(hModule, hPhongVertex);
        const char* psCode = (const char*)LockResource(hgPhongVertex);        
        return std::string(psCode, nSize);
    }

    SceneRenderer::SceneRenderer()
    : sky_box(nullptr)
    {
        #ifdef _MSC_VER
        HMODULE hModule = GetModuleHandle(_T("pkzo3d.dll"));

        std::string phong_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_VERTEX), _T("GLSL"));
        std::string phong_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_FRAGMENT), _T("GLSL"));

        std::string skybox_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SKYBOX_VERTEX), _T("GLSL"));
        std::string skybox_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SKYBOX_FRAGMENT), _T("GLSL"));
        
        std::string env_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_ENVIRONMENT_VERTEX), _T("GLSL"));
        std::string env_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_ENVIRONMENT_FRAGMENT), _T("GLSL"));

        std::string light_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_LIGHT_VERTEX), _T("GLSL"));
        std::string light_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_LIGHT_FRAGMENT), _T("GLSL"));
        #else
        // TODO
        #endif

        phong_shader.set_vertex_code(phong_vertex);
        phong_shader.set_fragment_code(phong_fragment);

        skybox_shader.set_vertex_code(skybox_vertex);
        skybox_shader.set_fragment_code(skybox_fragment);

        env_shader.set_vertex_code(env_vertex);
        env_shader.set_fragment_code(env_fragment);

        light_shader.set_vertex_code(light_vertex);
        light_shader.set_fragment_code(light_fragment);

        screen_rect.create_screen_plane();        
    }

    SceneRenderer::~SceneRenderer() {}

    void SceneRenderer::orient_camera(const mat4& projection, const mat4& view)
    {
        projection_matrix = projection;
        view_matrix       = view;
    }

    void SceneRenderer::set_sky_box(CubeMap & value)
    {
        sky_box = &value;
    }

    void SceneRenderer::queue_ambient_light(const vec3& color)
    {
        LightInfo info;
        info.type      = AMBIENT_LIGHT;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_directional_light(const vec3& direction, const vec3& color)
    {
        LightInfo info;
        info.type      = DIRECTIONAL_LIGHT;
        info.direction = direction;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_point_light(const vec3& position, const vec3& color, float range)
    {
        LightInfo info;
        info.type      = POINT_LIGHT;
        info.position  = position;
        info.range     = range;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_spot_light(const vec3& position, const vec3& direction, const vec3& color, float range, float angle)
    {
        LightInfo info;
        info.type      = SPOT_LIGHT;
        info.position  = position;
        info.direction = direction;
        info.color     = color;
        info.range     = range;
        info.angle     = angle;        

        lights.push_back(info);
    }

    void SceneRenderer::queue_geometry(mat4 transform, const Mesh& mesh, Material& material)
    {
        GeometryInfo info;
        info.transform = transform;
        info.mesh      = &mesh;
        info.material  = &material;

        geometries.push_back(info);
    }

    void SceneRenderer::render()
    {
        draw_sky_box();
        //draw_environment_pass();
        draw_lit_objects();

        sky_box = nullptr;
        lights.clear();
        geometries.clear();
    }

    void SceneRenderer::draw_sky_box()
    {
        if (sky_box != nullptr)
        {
            glDisable(GL_DEPTH_TEST);

            skybox_shader.bind();

            skybox_shader.set_uniform("uProjectionMatrix", projection_matrix);
            skybox_shader.set_uniform("uViewMatrix",       view_matrix);

            sky_box->bind(0);
            skybox_shader.set_uniform("uCubeMap", 0);

            screen_rect.draw();
        }
    }

    void SceneRenderer::draw_environment_pass()
    {
        if (sky_box != nullptr)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
        
            glDisable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);

            env_shader.bind();

            env_shader.set_uniform("uProjectionMatrix", projection_matrix);
            env_shader.set_uniform("uViewMatrix",       view_matrix);  
            
            sky_box->bind(0); // TODO coordinate with Material
            env_shader.set_uniform("uEnvMap",           0);        

            for (GeometryInfo& geom : geometries)
            {
                env_shader.set_uniform("uModelMatrix", geom.transform);
                
                geom.material->setup(env_shader);

                geom.mesh->draw();
            }

            // enable blending after the first pass.
            glEnable(GL_BLEND);
        }
    }

    void SceneRenderer::draw_lit_objects()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        
        glDisable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        light_shader.bind();

        light_shader.set_uniform("uProjectionMatrix", projection_matrix);
        light_shader.set_uniform("uViewMatrix",       view_matrix);        

        for (LightInfo& light : lights)
        {
            light_shader.set_uniform("uLightType",      light.type);
            light_shader.set_uniform("uLightDirection", light.direction);
            light_shader.set_uniform("uLightPosition",  light.position);
            light_shader.set_uniform("uLightRange",     light.range);
            light_shader.set_uniform("uLightCutoff",    1.0f - light.angle / 90.0f);
            light_shader.set_uniform("uLightColor",     light.color);

            for (GeometryInfo& geom : geometries)
            {
                mat4 model_view_matrix = view_matrix * geom.transform;
                //mat3 normal_matrix     = mat3(trans(inv(model_view_matrix)));                
                // this an OK, since the rotational part is orthogonal
                mat3 normal_matrix     = mat3(model_view_matrix);                
                
                light_shader.set_uniform("uModelMatrix",     geom.transform);
                light_shader.set_uniform("uModelViewMatrix", model_view_matrix);
                light_shader.set_uniform("uNormalMatrix",    normal_matrix);

                geom.material->setup(light_shader);

                geom.mesh->draw();
            }

            // enable blending after the first pass.
            glEnable(GL_BLEND);
        }
    } 
}