
#ifndef _PKZO_BOX_GEOMETRY_H_
#define _PKZO_BOX_GEOMETRY_H_

#include "Geometry.h"

namespace pkzo
{
    class PKZO_EXPORT BoxGeometry : public Geometry
    {
    public:
        BoxGeometry();

        ~BoxGeometry();

    private:
        static std::weak_ptr<Mesh> shared_mesh;
    };
}

#endif
