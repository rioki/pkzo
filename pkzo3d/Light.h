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

#include "Node.h"

namespace pkzo3d
{
    enum class LightType : int
    {
        NONE,
        AMBIENT,
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class PKZO3D_EXPORT Light : public Node
    {
    public:
        using Node::Specs;

        Light(Specs specs);

        ~Light();

        virtual LightType get_type() const = 0;
        virtual glm::vec3 get_color() const = 0;
        virtual glm::vec3 get_direction() const = 0;
        virtual glm::vec3 get_position() const = 0;
        virtual glm::vec2 get_angles() const = 0;
    };
}
