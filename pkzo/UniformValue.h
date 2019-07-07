// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_UNIFORM_VALUE_H_
#define _PKZO_UNIFORM_VALUE_H_

#include <variant>
#include <glm/glm.hpp>

#include "defines.h"

namespace pkzo
{
    /*!
     * Variant of all types that can be used as uniform variable.
     */
    typedef std::variant<bool, int, glm::uint, float, 
                         glm::ivec2, glm::uvec2, glm::vec2,
                         glm::ivec3, glm::uvec3, glm::vec3, 
                         glm::ivec4, glm::uvec4, glm::vec4, 
                         glm::mat2, glm::mat3, glm::mat4> UniformValue;
}

#endif
