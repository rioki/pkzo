
#ifndef _PKZOSG_SCENE_H_
#define _PKZOSG_SCENE_H_

#include "defines.h"

#include <list>
#include <vector>

#include "Color.h"

namespace pkzo
{
    class SceneRenderer;
    class SceneNode;

    class PKZO_EXPORT Scene
    {
    public:
        
        Scene();

        Scene(const Scene&) = delete;

        virtual ~Scene();

        const Scene& operator = (const Scene&) = delete;
        
        void add_node(SceneNode& node);

        void remove_node(SceneNode& node);

        template <typename Type>
        std::vector<Type*> get_nodes();

        template <typename Type>
        std::vector<const Type*> get_nodes() const;

        virtual void update(float t, float dt);

        virtual void render(SceneRenderer& renderer) const;

    private:
        // TODO spacial organisation structure
        std::list<SceneNode*> nodes;
    };

    template <typename Type>
    std::vector<Type*> Scene::get_nodes()
    {
        std::vector<Type*> result;    

        for (SceneNode* node : nodes)
        {
            Type* tnode = dynamic_cast<Type*>(node);
            if (tnode != nullptr)
            {
                result.push_back(tnode);
            }
        }

        return result;
    }

    template <typename Type>
    std::vector<const Type*> Scene::get_nodes() const
    {
        std::vector<const Type*> result;    

        for (SceneNode* node : nodes)
        {
            Type* tnode = dynamic_cast<const Type*>(node);
            if (tnode != nullptr)
            {
                result.push_back(tnode);
            }
        }

        return result;
    }
}

#endif
