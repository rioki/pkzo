
#include "SceneRenderer.h"

namespace pkzo
{
    SceneRenderer::SceneRenderer() {}

    SceneRenderer::~SceneRenderer() {}

    void SceneRenderer::set_projection(Matrix4 value)
    {
        projection = value;
    }

    void SceneRenderer::set_view(Matrix4 value)
    {
        view = value;
    }

    void SceneRenderer::queue_directional_light(const Vector3& diraction, const Color& color)
    {

    }

    void SceneRenderer::queue_geometry(Matrix4 transform, std::shared_ptr<Mesh> mesh , std::shared_ptr<Material> material)
    {

    }

    void SceneRenderer::render()
    {

    }
}
