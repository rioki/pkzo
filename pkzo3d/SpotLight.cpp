/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "SpotLight.h"

#include "SceneRenderer.h"

namespace pkzo
{
    SpotLight::SpotLight() 
    : range(10), angle(25) {}

    SpotLight::~SpotLight() {}

    void SpotLight::set_range(float value)
    {
        range = value;
    }

    float SpotLight::get_range() const
    {
        return range;
    }

    void SpotLight::set_angle(float value)
    {
        angle = value;
    }

    float SpotLight::get_angle() const
    {
        return angle;
    }

    void SpotLight::enqueue(SceneRenderer& renderer, const Camera& camera) const
    {
        quat o   = get_world_orientation();
        vec3 dir = transform(o, vec3(0, 0, 1));

        renderer.queue_spot_light(get_world_position(), dir, get_color(), range, angle);
    }
}