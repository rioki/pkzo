
#include "PhysicsKernel.h"

namespace pkzo
{
    PhysicsKernel::PhysicsKernel(Engine& engine)
    : world(0), space(0), accum(0)
    {
        dInitODE();
        world = dWorldCreate();
        space = dHashSpaceCreate(0);
    }

    PhysicsKernel::~PhysicsKernel()
    {
        dSpaceDestroy(space);
        dWorldDestroy(world);
        dCloseODE();
    }

    void nearCallback(void *data, dGeomID o1, dGeomID o2)
    {
        // TODO
    }

    void PhysicsKernel::update(float t, float dt)
    {
        dSpaceCollide(space, 0, &nearCallback);
    
        accum += dt;
        
        while (accum > 0.01)
        {
            dWorldQuickStep(world, 0.01); 
            accum -= 0.1;
        }
    }
}