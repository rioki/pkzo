
#include "Camera.h"

#include "SceneRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Matrix4.h"
#include "Vector3.h"

namespace pkzo
{
    Camera::Camera()
    : field_of_view(90.0f), view_distance(1000.0f) {}

    Camera::~Camera() {}

    void Camera::set_field_of_view(float value)
    {
        field_of_view = value;
    }

    float Camera::get_field_of_view() const
    {
        return field_of_view;
    }

    void Camera::set_view_distance(float value)
    {
        view_distance = value;
    }

    float Camera::get_view_distance() const
    {
        return view_distance;
    }
    
    Matrix4 frustum(float left, float right, float bottom, float top, float znear, float zfar)
    {
        float temp1 = 2.0f * znear;
        float temp2 = right - left;
        float temp3 = top - bottom;
        float temp4 = zfar - znear;

        // NOTE: this may need to be inversed, since rgm confuses row and column on the construct
        return Matrix4(temp1/temp2,        0.0f,  (right + left) / temp2,                    0.0f,
                              0.0f, temp1/temp3,  (top + bottom) / temp3,                    0.0f,
                              0.0f,        0.0f, (-zfar - znear) / temp4, (-temp1 * zfar) / temp4,
                              0.0f,        0.0f,                   -1.0f,                    0.0f);       
    }
    
    Matrix4 perspective(float fov, float aspect, float znear, float zfar)
    {
        float ymax = znear * std::tan(fov * ((float)M_PI / 180.0f));
        float xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    void Camera::enqueue(SceneRenderer& renderer) const
    {
        int x, y, w, h;
        std::tie(x, y, w, h) = renderer.get_viewport();
        
        float aspect = (float)w / (float)h;
        float znear  = 0.01;
        float yfov   = (field_of_view / 2.0f) / aspect;

        Matrix4 projection = perspective(yfov, aspect, znear, view_distance);

        Quaternion o  = get_world_orientation();
        Vector3    vx = transform(o, Vector3(1, 0, 0));
        Vector3    vy = transform(o, Vector3(0, 1, 0));
        Vector3    vz = transform(o, Vector3(0, 0, 1));

        Matrix4 view(vx[0], vx[1], vx[2], 0.0f,
                     vy[0], vy[1], vy[2], 0.0f,
                     vz[0], vz[1], vz[2], 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);

        Vector3 pc = transform(view, -get_world_position());
        view[12] = pc[0];
        view[13] = pc[1];
        view[14] = pc[2];
        
        renderer.set_projection(projection);
        renderer.set_view(view);
    }
}
