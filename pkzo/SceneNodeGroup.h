
#ifndef _PKZO_SCENE_NODE_GROUP_H_
#define _PKZO_SCENE_NODE_GROUP_H_

#include "SceneNode.h"

#include <vector>

namespace pkzo
{
    class PKZO_EXPORT SceneNodeGroup : public SceneNode
    {
    public:
        SceneNodeGroup();

        ~SceneNodeGroup();

        void add_node(SceneNode& node);

        void remove_node(SceneNode& node);

        void update(float t, float dt) override;

        void enqueue(SceneRenderer& renderer) const override;

    private:
        std::vector<SceneNode*> nodes;
    };
}

#endif
