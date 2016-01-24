
#ifndef _PKZOSG_GEOMETRY_H_
#define _PKZOSG_GEOMETRY_H_

#include "SceneNode.h"

#include <memory>

namespace pkzo
{
    class Mesh;
    class Material;

    class PKZO_EXPORT Geometry : public SceneNode
    {
    public:
        
        Geometry();

        ~Geometry();

        void set_material(std::shared_ptr<Material> value);

        std::shared_ptr<Material> get_material() const;
        
    protected:        
        std::shared_ptr<Material> material;
    };
}

#endif
