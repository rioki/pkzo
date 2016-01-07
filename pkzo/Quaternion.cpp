
#include "Quaternion.h"

#include <cassert>
#include <cstring>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector3.h"

namespace pkzo
{
    float radians(float degrees) 
    {
        return degrees * ((float)M_PI / 180.0f);
    }

    Quaternion Quaternion::axis_angle(float angle, const Vector3& axis)
    {
        Vector3 an  = normalize(axis);
        float sin_a = std::sin(radians(angle/2.0f));
        float cos_a = std::cos(radians(angle/2.0f));
           
        float x = an[0] * sin_a;
        float y = an[1] * sin_a;
        float z = an[2] * sin_a;
        float  w = cos_a;
          
        return Quaternion(x, y, z, w);
    }

    Quaternion::Quaternion()
    {
        std::memset(data, 0, 4 * sizeof(float));  
    }

    Quaternion::Quaternion(float x, float y, float z, float w)
    {    
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    Quaternion::Quaternion(const Quaternion& other)
    {
        std::memcpy(data, other.data, 4 * sizeof(float));
    }

    Quaternion::~Quaternion() {}

    const Quaternion& Quaternion::operator = (const Quaternion& other)
    {
        std::memcpy(data, other.data, 4 * sizeof(float));
        return *this;
    }

    const Quaternion& Quaternion::operator += (const Quaternion& other)
    {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        data[3] += other.data[3];
        return *this;
    }

    const Quaternion& Quaternion::operator -= (const Quaternion& other)
    {
        data[0] -= other.data[0];
        data[1] -= other.data[1];
        data[2] -= other.data[2];
        data[3] -= other.data[3];
        return *this;
    }

    const Quaternion& Quaternion::operator *= (const Quaternion& other)
    {
        float   wa = data[3];
        Vector3 va = Vector3(data[0], data[1], data[2]);
        float   wb = other.data[3];
        Vector3 vb = Vector3(other.data[0], other.data[1], other.data[2]);
  
        float   w = wa * wb - dot(va, vb);
        Vector3 v = vb * wa + va * wb + cross(va, vb);

        data[0] = v[0];
        data[1] = v[1];
        data[2] = v[2];
        data[3] = w;

        return *this;
    }

    float& Quaternion::operator [] (unsigned int i)
    {
        assert(i < 4);
        return data[i];
    }

    float Quaternion::operator [] (unsigned int i) const
    {
        assert(i < 4);
        return data[i];
    }

    const float* Quaternion::carray() const
    {
        return data;
    }
    
    Quaternion operator + (const Quaternion& a, const Quaternion& b)
    {
        Quaternion t = a;
        t += b;
        return t;
    }

    Quaternion operator - (const Quaternion& a, const Quaternion& b)
    {
        Quaternion t = a;
        t -= b;
        return t;
    }

    Quaternion operator * (const Quaternion& a, const Quaternion& b)
    {
        Quaternion t = a;
        t *= b;
        return t;
    }

    Quaternion normalize(const Quaternion& q)
    {
        float len = std::sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
        return Quaternion(q[0] / len, q[1] / len, q[2] / len, q[3] / len);
    }

    Quaternion inverse(const Quaternion& q)
    {
        return Quaternion(-q[0], -q[1], -q[2], q[3]);
    }

    Vector3 transform(const Quaternion& q, const Vector3& v)
    {
        Quaternion qn = normalize(q);
        Quaternion qi = inverse(qn);
        Quaternion qv = Quaternion(v[0], v[1], v[2], 0);
        Quaternion qr = qn * qv * qi;
        return Vector3(qr[0], qr[1], qr[2]);
    }
}
