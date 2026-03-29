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

#include "Light.h"

namespace pkzo
{
    class PKZO_EXPORT DirectionalLight : public Light
    {
    public:
        struct Init
        {
            Node*     parent    = nullptr;
            glm::mat4 transform = glm::mat4(1.0f);
            glm::vec3 color     = glm::vec3(0.1f);
        };

        DirectionalLight(Init init);
        ~DirectionalLight();

        void set_color(const glm::vec3& value);

        LightType get_type() const override;
        glm::vec3 get_color() const override;
        glm::vec3 get_direction() const override;
        glm::vec3 get_position() const override;
        glm::vec2 get_angles() const override;

    private:
        glm::vec3 color;
    };
}
