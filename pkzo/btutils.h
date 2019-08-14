// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_BTUTILS_H_
#define _PKZO_BTUTILS_H_


#include <bullet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace pkzo
{
    inline
    btTransform to_bt(const glm::mat4& trans)
    {
        auto result = btTransform{};
        result.setFromOpenGLMatrix(glm::value_ptr(trans));
        return result;
    }

    inline
    glm::mat4 to_glm(const btTransform& trans)
    {
        auto result = glm::mat4(1.0f);
        trans.getOpenGLMatrix(glm::value_ptr(result));
        return result;
    }

    inline
    btVector3 to_bt(const glm::vec3& vec)
    {
        return {vec.x, vec.y, vec.z};
    }

    inline
    glm::vec3 to_glm(const btVector3& vec)
    {
        return {vec[0], vec[1], vec[2]};
    }
}

#endif

