
#ifndef _PKZOSG_SCENE_NODE_H_
#define _PKZOSG_SCENE_NODE_H_

#include "defines.h"

#include "Vector3.h"
#include "Quaternion.h"

namespace pkzo
{
    class SceneRenderer;

    class PKZO_EXPORT SceneNode
    {
    public:
        
        SceneNode();

        SceneNode(const SceneNode&) = delete;

        virtual ~SceneNode();

        const SceneNode& operator = (const SceneNode&) = delete;

        void set_position(const Vector3& value);

        const Vector3& get_position() const;

        Vector3 get_world_position() const;

        void set_orientation(const Quaternion& value);

        const Quaternion& get_orientation() const;

        Quaternion get_world_orientation() const;

        virtual void update(float t, float dt);

        virtual void enqueue(SceneRenderer& renderer) const = 0;

    private:
        SceneNode* parent;
        Vector3  position;
        Quaternion  orientation;
    };
}

#endif
