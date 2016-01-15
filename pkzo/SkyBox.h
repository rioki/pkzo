
#ifndef _PKZO_SKY_BOX_H_
#define _PKZO_SKY_BOX_H_

#include "SceneNode.h"

#include <memory>

namespace pkzo
{
    class CubeMap;

    class PKZO_EXPORT SkyBox : public SceneNode
    {
    public:
        SkyBox();

        ~SkyBox();

        void set_cubemap(std::shared_ptr<CubeMap> value);

        std::shared_ptr<CubeMap> get_cubemap() const;

        void enqueue(SceneRenderer& renderer) const override;

    private:
        std::shared_ptr<CubeMap> cubemap;
    };
}

#endif
