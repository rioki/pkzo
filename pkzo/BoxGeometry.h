// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_BOX_GEOMETRY_H_
#define _PKZO_BOX_GEOMETRY_H_

#include "Geometry.h"

namespace pkzo
{
    class Mesh;

    //! Box Geometry
    class PKZO_EXPORT BoxGeometry : public Geometry
    {
    public:
        BoxGeometry(const glm::vec3& size, const std::shared_ptr<Material>& material);

        ~BoxGeometry();

        //! Set the box's size
        void set_size(const glm::vec3& value);

        //! Get the box's size
        const glm::vec3& get_size() const;

        void enqueue(RenderQueue& queue) const override;
        void activate() override;
        void deactivate() override;
        void update(float dt) override;

    private:
        glm::vec3 size;
    };
}

#endif
