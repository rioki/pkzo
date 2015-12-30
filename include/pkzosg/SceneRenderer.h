
#ifndef _PKZOSG_SCENE_RENDERER_H_
#define _PKZOSG_SCENE_RENDERER_H_

#include "defines.h"

#include <memory>
#include <list>
#include <pkzo/Vector3.h>
#include <pkzo/Matrix4.h>
#include <pkzo/Color.h>
#include <pkzo/Shader.h>

namespace pkzo
{
    class Mesh;
    class Material;
    
    class PKZOSG_EXPORT SceneRenderer
    {
    public:
        
        SceneRenderer();

        SceneRenderer(const SceneRenderer&) = delete;

        ~SceneRenderer();

        const SceneRenderer& operator = (const SceneRenderer&) = delete;

        void set_projection(Matrix4 value);

        void set_view(Matrix4 value);

        void queue_directional_light(const Vector3& diraction, const Color& color);

        void queue_geometry(Matrix4 transform, std::shared_ptr<Mesh> mesh , std::shared_ptr<Material> material);

        void render();

    private:
        
        enum LightType 
        {
            DIRECTIONAL_LIGHT,
            POINT_LIGHT,
            SPOT_LIGHT
        };

        struct LightInfo
        {
            LightType type;
            Vector3 direction;
            Vector3 position;
            float     angle;
            Vector3 color;
        };

        struct GeometryInfo
        {
            Matrix4                 transform;
            std::shared_ptr<Mesh>     mesh;
            std::shared_ptr<Material> material;
        };

        Matrix4               projection;
        Matrix4               view;
        std::list<LightInfo>    lights;
        std::list<GeometryInfo> geometries;

        Shader                  diffuse_shader;
    };
};

#endif

