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

#include "Camera.h"

namespace pkzo
{
    Camera::Camera()
    : fov(90), distance(1000) {}

    Camera::~Camera() {}

    void Camera::set_fov(float value)
    {
        fov = value;
    }

    float Camera::get_fov() const
    {
        return fov;
    }

    void Camera::set_distance(float value)
    {
        distance = value;
    }

    float Camera::get_distance() const
    {
        return distance;
    }

    mat4 Camera::get_projection_matrix(float aspect) const
    {
        //float aspect = (float)w / (float)h;
        float znear  = 0.01;
        float yfov   = (fov / 2.0f) / aspect;
        
        return perspective(yfov, aspect, znear, distance);
    }

    mat4 Camera::get_view_matrix() const
    {
        quat o  = get_world_orientation();
        vec3 vx = transform(o, vec3(1, 0, 0));
        vec3 vy = transform(o, vec3(0, 1, 0));
        vec3 vz = transform(o, vec3(0, 0, 1));

        vec3 pc = -get_world_position();

        mat4 mp(1.0f, 0.0f, 0.0f, pc[0],
                0.0f, 1.0f, 0.0f, pc[1], 
                0.0f, 0.0f, 1.0f, pc[2],
                0.0f, 0.0f, 0.0f,  1.0f);

        mat4 mo(vx[0], vx[1], vx[2], 0.0f,
                vy[0], vy[1], vy[2], 0.0f,
                vz[0], vz[1], vz[2], 0.0f,
                 0.0f,  0.0f,  0.0f, 1.0f);
        
        return mp * mo;
    }

    void Camera::enqueue(SceneRenderer& queue, const Camera& camera) const
    {
        // do nothing
    }
}