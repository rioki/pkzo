
#ifndef _PKZO_CAMERA_H_
#define _PKZO_CAMERA_H_

#include "SceneNode.h"

namespace pkzo
{
    class PKZO_EXPORT Camera : public SceneNode
    {
    public:

        Camera();

        ~Camera();

        void set_field_of_view(float value);

        float get_field_of_view() const;

        void set_view_distance(float value);

        float get_view_distance() const;

        void enqueue(SceneRenderer& renderer) const override;

    private:
        float field_of_view;
        float view_distance;
    };
}

#endif
