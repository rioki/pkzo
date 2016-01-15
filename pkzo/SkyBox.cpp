
#include "SkyBox.h"

#include "SceneRenderer.h"

namespace pkzo
{
    SkyBox::SkyBox() {}

    SkyBox::~SkyBox() {}

    void SkyBox::set_cubemap(std::shared_ptr<CubeMap> value)
    {
        cubemap = value;
    }

    std::shared_ptr<CubeMap> SkyBox::get_cubemap() const
    {
        return cubemap;
    }

    void SkyBox::enqueue(SceneRenderer& renderer) const
    {
        renderer.set_background(*cubemap);
    }
}