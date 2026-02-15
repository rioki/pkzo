// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <glm/glm.hpp>
#include <fkYAML/node.hpp>
#include <glm_fkyaml.h>

namespace pkzo
{
    constexpr
    glm::vec3 rgb(float r, float g, float b)
    {
        return { r, g, b };
    }

    constexpr
    glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b)
    {
        return rgb((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
    }

    constexpr
    glm::vec3 rgb(unsigned int hex)
    {
        unsigned int r = (hex & 0x00FF0000) >> 16;
        unsigned int g = (hex & 0x0000FF00) >> 8;
        unsigned int b = (hex & 0x000000FF) >> 0;
        return rgb(r, g, b);
    }

    constexpr
    glm::vec4 rgba(float r, float g, float b, float a)
    {
        return { r, g, b, a };
    }

    constexpr
    glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    {
        return rgba((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
    }

    constexpr
    glm::vec4 rgba(unsigned int hex)
    {
        unsigned int r = (hex & 0xFF000000) >> 24;
        unsigned int g = (hex & 0x00FF0000) >> 16;
        unsigned int b = (hex & 0x0000FF00) >> 8;
        unsigned int a = (hex & 0x000000FF) >> 0;
        return rgba(r, g, b, a);
    }

    // Yaml serialisation helpers
    struct color4
    {
        glm::vec4 value;

        operator glm::vec4 ()
        {
            return value;
        }
    };

    struct color3
    {
        glm::vec3 value;

        operator glm::vec3 ()
        {
            return value;
        }
    };

    inline void from_node(const fkyaml::node& node, color4& v)
    {
        if (node.is_integer())
        {
            v.value = rgba(static_cast<unsigned int>(node.as_int()));
        }
        else if (node.is_sequence() && node.as_seq().size() == 4)
        {
            v.value = node.get_value<glm::vec4>();
        }
        else
        {
            throw std::runtime_error("color4: no idea what you gave me");
        }
    }

    inline void from_node(const fkyaml::node& node, color3& v)
    {
        if (node.is_integer())
        {
            v.value = rgb(static_cast<unsigned int>(node.as_int()));
        }
        else if (node.is_sequence() && node.as_seq().size() == 3)
        {
            v.value = node.get_value<glm::vec3>();
        }
        else
        {
            throw std::runtime_error("color3: no idea what you gave me");
        }
    }
}