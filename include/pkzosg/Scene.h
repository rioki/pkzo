
#ifndef _PKZOSG_SCENE_H_
#define _PKZOSG_SCENE_H_

#include "defines.h"

#include <list>

namespace pkzo
{
    class SceneRenderer;
    class SceneNode;

    class PKZOSG_EXPORT Scene
    {
    public:
        
        Scene();

        Scene(const Scene&) = delete;

        virtual ~Scene();

        const Scene& operator = (const Scene&) = delete;
        
        void add_node(SceneNode& node);

        void remove_node(SceneNode& node);

        virtual void update(float t, float dt);

        virtual void render(SceneRenderer& renderer) const;

    private:
        // TODO spacial organisation structure
        std::list<SceneNode*> nodes;
    };
}

#endif
