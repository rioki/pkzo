// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "config.h"

#include "Light.h"

namespace pkzo
{
    class ICE_EXPORT SpotLight : public Light
    {
    public:
        SpotLight() noexcept = default;
        SpotLight(const glm::mat4& transform, const glm::vec3& color, float inner_angle, float outer_angle) noexcept;

        void set_color(const glm::vec3& value) noexcept;
        const glm::vec3& get_color() const noexcept;

        void set_inner_angle(float value) noexcept;
        float get_inner_angle() const noexcept;

        void set_outer_angle(float value) noexcept;
        float get_outer_angle() const noexcept;

    protected:
        unsigned int register_light(Renderer& renderer) noexcept override;

    private:
        glm::vec3 color       = glm::vec3(1.0f);
        float     inner_angle = 25.0f;
        float     outer_angle = 30.0f;
    };
}
