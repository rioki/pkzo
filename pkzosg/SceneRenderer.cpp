
#include "SceneRenderer.h"

#include <pkzo/Mesh.h>
#include "Material.h"

#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#else
// TODO ezrc
#endif

#include <GL/glew.h>

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
    {
        #ifdef _MSC_VER
        HMODULE hModule = GetModuleHandle(_T("pkzosg.dll"));

        std::string phong_vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_VERTEX), _T("GLSL"));
        std::string phong_fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_PHONG_FRAGMENT), _T("GLSL"));
        #else
        // TODO
        #endif

        phong_shader.set_vertex_code(phong_vertex);
        phong_shader.set_fragment_code(phong_fragment);
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

    void SceneRenderer::queue_directional_light(const Vector3& direction, const Color& color)
    {
        LightInfo info;
        info.type      = DIRECTIONAL_LIGHT;
        info.direction = direction;
        info.color     = color;

        lights.push_back(info);
    }

    void SceneRenderer::queue_geometry(Matrix4 transform, std::shared_ptr<Mesh> mesh , std::shared_ptr<Material> material)
    {
        GeometryInfo info;
        info.transform = transform;
        info.mesh      = mesh;
        info.material  = material;

        geometries.push_back(info);
    }

    void SceneRenderer::render()
    {
        glEnable(GL_DEPTH_TEST);

        phong_shader.bind();

        phong_shader.set_uniform_matrix("uProjectionMatrix", projection.carray(), 16);
        phong_shader.set_uniform_matrix("uViewMatrix",       view.carray(),       16);

        for (LightInfo& light : lights)
        {
            phong_shader.set_uniform("uLightType",      light.type);
            phong_shader.set_uniform("uLightDirection", light.direction.carray(), 3);
            phong_shader.set_uniform("uLightPosition",  light.position.carray(),  3);
            phong_shader.set_uniform("uLightAngle",     light.angle);
            phong_shader.set_uniform("uLightColor",     light.color.carray(),     3);

            for (GeometryInfo& geom : geometries)
            {
                Matrix4 mv = view * geom.transform;
               
                phong_shader.set_uniform_matrix("uModelViewMatrix", mv.carray(), 16);
                
                geom.material->setup(phong_shader);
                geom.mesh->draw(phong_shader);
            }
        }

        lights.clear();
        geometries.clear();
    }
}
