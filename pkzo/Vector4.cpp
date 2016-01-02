
#include "Vector4.h"

#include <cassert>
#include <cstring>
#include <cmath>

namespace pkzo
{
    Vector4::Vector4()
    {
        std::memset(data, 0, 4 * sizeof(float));        
    }

    Vector4::Vector4(float v)
    {
        data[0] = v;
        data[1] = v;
        data[2] = v;
        data[3] = v;
    }

    Vector4::Vector4(float x, float y, float z, float m)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = m;
    }

    Vector4::Vector4(const Vector4& other)
    {
        std::memcpy(data, other.data, 4 * sizeof(float));
    }

    Vector4::~Vector4() {}

    const Vector4& Vector4::operator = (const Vector4& other)
    {
        std::memcpy(data, other.data, 4 * sizeof(float));
        return *this;
    }

    const Vector4& Vector4::operator += (const Vector4& other)
    {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        data[3] += other.data[3];
        return *this;
    }

    const Vector4& Vector4::operator -= (const Vector4& other)
    {
        data[0] -= other.data[0];
        data[1] -= other.data[1];
        data[2] -= other.data[2];
        data[3] -= other.data[3];
        return *this;
    }

    float& Vector4::operator [] (unsigned int i)
    {
        assert(i < 4);
        return data[i];
    }

    float Vector4::operator [] (unsigned int i) const
    {
        assert(i < 4);
        return data[i];
    }

    Vector4::operator const float* () const
    {
        return data;
    }
    
    Vector4 operator - (const Vector4& v)
    {
        return Vector4(-v[0], -v[1], -v[2], -v[3]);
    }

    Vector4 operator + (const Vector4& a, const Vector4& b)
    {
        Vector4 t = a;
        t += b;
        return t;
    }
    
    Vector4 operator - (const Vector4& a, const Vector4& b)
    {
        Vector4 t = a;
        t -= b;
        return t;
    }
    
    Vector4 operator * (const Vector4& v, float s)
    {
        return Vector4(v[0] * s, v[1] * s, v[2] * s, v[3] * s);
    }
    
    Vector4 operator * (float s, const Vector4& v)
    {
        return v * s;
    }
    
    float dot(const Vector4& a, const Vector4& b)
    {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] +  a[3] * b[3];
    }
    
    float length(Vector4& v)
    {
        return std::sqrt(dot(v, v));
    }
    
    Vector4 normalize(Vector4& v)
    {
        return v * (1 / length(v));
    }
}
