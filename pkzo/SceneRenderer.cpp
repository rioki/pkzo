
#include "SceneRenderer.h"

#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#else
// TODO ezrc
#endif

#include <GL/glew.h>

#include "Matrix3.h"
#include "Mesh.h"
#include "Material.h"
#include "CubeMap.h"

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
    : background(nullptr)
    {
        #ifdef _MSC_VER
        HMODULE hModule = GetModuleHandle(_T("pkzo.dll"));

        std::string phong_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_VERTEX), _T("GLSL"));
        std::string phong_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_FRAGMENT), _T("GLSL"));
        std::string skybox_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SKYBOX_VERTEX), _T("GLSL"));
        std::string skybox_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_SKYBOX_FRAGMENT), _T("GLSL"));
        #else
        // TODO
        #endif

        skybox_shader.set_vertex_code(skybox_vertex);
        skybox_shader.set_fragment_code(skybox_fragment);

        phong_shader.set_vertex_code(phong_vertex);
        phong_shader.set_fragment_code(phong_fragment);

        screen_mesh.create_screen_plane();
    }

    SceneRenderer::~SceneRenderer() {}

    std::tuple<int, int, int, int> SceneRenderer::get_viewport() const
    {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        return std::make_tuple(viewport[0], viewport[1], viewport[2], viewport[3]);
    }

    void SceneRenderer::set_projection(const Matrix4& value)
    {
        projection = value;
    }

    void SceneRenderer::set_view(const Matrix4& value)
    {
        view = value;
    }

    void SceneRenderer::set_background(const CubeMap& value)
    {
        background = &value;
    }

    void SceneRenderer::queue_ambient_light(const Color& color)
    {
        LightInfo info;
        info.type      = AMBIENT_LIGHT;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_directional_light(const Vector3& direction, const Color& color)
    {
        LightInfo info;
        info.type      = DIRECTIONAL_LIGHT;
        info.direction = direction;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_point_light(const Vector3& position, const Color& color, float range)
    {
        LightInfo info;
        info.type      = POINT_LIGHT;
        info.position  = position;
        info.range     = range;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_spot_light(const Vector3& position, const Vector3& direction, const Color& color, float range, float angle)
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

    void SceneRenderer::queue_geometry(Matrix4 transform, const Mesh& mesh , const Material& material)
    {
        GeometryInfo info;
        info.transform = transform;
        info.mesh      = &mesh;
        info.material  = &material;

        geometries.push_back(info);
    }

    void SceneRenderer::render()
    {
        render_background();
        render_geometry();

        background = nullptr;
        lights.clear();
        geometries.clear();
    }

    void SceneRenderer::render_background()
    {
        if (background != nullptr)
        {
            glDisable(GL_DEPTH_TEST);

            skybox_shader.bind();

            skybox_shader.set_uniform_matrix("uProjectionMatrix", projection.carray(), 16);
            skybox_shader.set_uniform_matrix("uViewMatrix",       view.carray(),       16);

            background->bind(0);
            skybox_shader.set_uniform("uCubeMap", 0);

            screen_mesh.draw(skybox_shader);
        }
    }

    void SceneRenderer::render_geometry()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        
        glDisable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);

        phong_shader.bind();

        Matrix3 view3(view); 

        phong_shader.set_uniform_matrix("uProjectionMatrix", projection.carray(), 16);
        phong_shader.set_uniform_matrix("uViewMatrix",       view.carray(),       16);        

        for (LightInfo& light : lights)
        {
            phong_shader.set_uniform("uLightType",      light.type);
            phong_shader.set_uniform("uLightDirection", light.direction.carray(), 3);
            phong_shader.set_uniform("uLightPosition",  light.position.carray(),  3);
            phong_shader.set_uniform("uLightRange",     light.range);
            phong_shader.set_uniform("uLightCutoff",    1.0f - light.angle / 90.0f);
            phong_shader.set_uniform("uLightColor",     light.color.carray(),     3);

            for (GeometryInfo& geom : geometries)
            {
                Matrix4 model_view = geom.transform * view;
                
                phong_shader.set_uniform_matrix("uModelMatrix",     geom.transform.carray(), 16);
                phong_shader.set_uniform_matrix("uModelViewMatrix", model_view.carray(), 16);                
                
                geom.material->setup(phong_shader);
                geom.mesh->draw(phong_shader);
            }

            // enable blending after the first pass.
            glEnable(GL_BLEND);
        }
    }
}
