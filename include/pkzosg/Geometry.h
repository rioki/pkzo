
#ifndef _PKZOSG_GEOMETRY_H_
#define _PKZOSG_GEOMETRY_H_

#include "SceneNode.h"

#include <memory>

namespace pkzo
{
    class Mesh;
    class Material;

    class PKZOSG_EXPORT Geometry : public SceneNode
    {
    public:
        
        Geometry();

        ~Geometry();

        void set_mesh(std::shared_ptr<Mesh> value);

        std::shared_ptr<Mesh> get_mesh() const;

        void set_material(std::shared_ptr<Material> value);

        std::shared_ptr<Material> get_material() const;

        void enqueue(SceneRenderer & renderer) const override;

    private:
        std::shared_ptr<Mesh>     mesh;
        std::shared_ptr<Material> material;
    };
}

#endif
