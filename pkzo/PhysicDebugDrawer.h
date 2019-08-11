// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_PHYSIC_DEBUG_DRAWER_H_
#define _PKZO_PHYSIC_DEBUG_DRAWER_H_

#include <bullet/btBulletDynamicsCommon.h>

namespace pkzo
{
    class DebugDrawer;

    class PhysicDebugDrawer : public btIDebugDraw
    {
    public:

        PhysicDebugDrawer(std::shared_ptr<DebugDrawer> drawer);

        void drawLine(const btVector3& from,const btVector3& to,const btVector3& color) override;
        void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
        void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) override;
        void reportErrorWarning(const char* warningString) override;
        void draw3dText(const btVector3& location,const char* textString) override;
        void setDebugMode(int debugMode) override;
        int getDebugMode() const override;

    private:
        int debugMode = 0;
        std::shared_ptr<DebugDrawer> drawer;
    };
}

#endif
