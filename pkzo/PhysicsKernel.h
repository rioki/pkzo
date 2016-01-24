
#ifndef _PKZO_PHYSICS_KERNEL_H_
#define _PKZO_PHYSICS_KERNEL_H_

#define dSINGLE 

#include <vector>
#include <ode/ode.h>

namespace pkzo
{
    class Engine;

    class PhysicsKernel
    {
    public:

        PhysicsKernel(Engine& engine);

        PhysicsKernel(const PhysicsKernel&) = delete;

        ~PhysicsKernel();

        const PhysicsKernel& operator = (const PhysicsKernel&) = delete;

        void update(float t, float dt);

    private:
        dWorldID world;
        dSpaceID space;
        float accum;
        
        //std::vector<dBodyID> bodies;
        //std::vector<dGeomID> geoms;        
    };
}

#endif
