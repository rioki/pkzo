
#include "Geometry.h"

#include "SceneRenderer.h"

namespace pkzo
{
    Geometry::Geometry() {}

    Geometry::~Geometry() {}

    void Geometry::set_mesh(std::shared_ptr<Mesh> value) 
    {
        mesh = value;
    }

    std::shared_ptr<Mesh> Geometry::get_mesh() const
    {
        return mesh;
    }

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = value;
    }

    std::shared_ptr<Material> Geometry::get_material() const
    {
        return material;
    }

    void Geometry::enqueue(SceneRenderer & renderer) const
    {        
        if (mesh && material)
        {        
            Quaternion o = get_world_orientation();
            Vector3    x = transform(o, Vector3(1, 0, 0));  
            Vector3    y = transform(o, Vector3(0, 1, 0));  
            Vector3    z = transform(o, Vector3(0, 0, 1));  
            Vector3    p = get_world_position();

            Matrix4 t(x[0], y[0], z[0], p[0],
                      x[1], y[1], z[1], p[1],
                      x[2], y[2], z[2], p[2],
                      0.0f, 0.0f, 0.0f, 1.0f);

            renderer.queue_geometry(t, *mesh, *material);
        }
    }
}
