#include "pch.h"
#include "PhysicDebugDrawer.h"

#include "dbg.h"
#include "DebugDrawer.h"

namespace pkzo
{
    glm::vec3 to_glm(const btVector3& vec);

    PhysicDebugDrawer::PhysicDebugDrawer(std::shared_ptr<DebugDrawer> d)
    : drawer(d) {}

    void PhysicDebugDrawer::drawLine(const btVector3& from,const btVector3& to, const btVector3& color)
    {
        assert(drawer);
        drawer->draw_line(to_glm(from), to_glm(to), glm::vec4(to_glm(color), 1.0f), glm::vec4(to_glm(color), 1.0f));
    }

    void PhysicDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
    {
        assert(drawer);
        drawer->draw_line(to_glm(from), to_glm(to), glm::vec4(to_glm(fromColor), 1.0f), glm::vec4(to_glm(toColor), 1.0f));
    }

    void PhysicDebugDrawer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
    {
        // TODO
    }

    void PhysicDebugDrawer::reportErrorWarning(const char* warningString)
    {
        PKZO_TRACE_ERROR(warningString);
    }

    void PhysicDebugDrawer::draw3dText(const btVector3& location,const char* textString)
    {
        // TODO
    }

    void PhysicDebugDrawer::setDebugMode(int value)
    {
        debugMode = value;
    }

    int PhysicDebugDrawer::getDebugMode() const
    {
       return debugMode;
    }

}
