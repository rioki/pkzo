
#ifndef _PKZOSG_SCENE_RENDERER_H_
#define _PKZOSG_SCENE_RENDERER_H_

#include "defines.h"

#include <list>
#include <tuple>
#include "Vector3.h"
#include "Matrix4.h"
#include "Color.h"
#include "Shader.h"
#include "Mesh.h"

namespace pkzo
{
    class Mesh;
    class Material;
    class CubeMap;
    
    class PKZO_EXPORT SceneRenderer
    {
    public:
        
        SceneRenderer();

        SceneRenderer(const SceneRenderer&) = delete;

        ~SceneRenderer();

        const SceneRenderer& operator = (const SceneRenderer&) = delete;

        std::tuple<int, int, int, int> get_viewport() const;

        void set_projection(const Matrix4& value);

        void set_view(const Matrix4& value);

        void set_background(const CubeMap& cubemap);

        void queue_ambient_light(const Color& color);

        void queue_directional_light(const Vector3& direction, const Color& color);

        void queue_point_light(const Vector3& position, const Color& color, float range);

        void queue_spot_light(const Vector3& position, const Vector3& direction, const Color& color, float range, float angle);

        void queue_geometry(Matrix4 transform, const Mesh& mesh , const Material& material);

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
            Vector3   direction;
            Vector3   position;
            float     range;
            float     angle;
            Color     color;
        };

        struct GeometryInfo
        {
            Matrix4         transform;
            const Mesh*     mesh;
            const Material* material;
        };

        Matrix4                 projection;
        Matrix4                 view;
        const CubeMap*          background;
        std::list<LightInfo>    lights;
        std::list<GeometryInfo> geometries;

        Shader                  skybox_shader;
        Shader                  phong_shader;

        Mesh                    screen_mesh;

        void render_background();
        void render_geometry();
    };
};

#endif

