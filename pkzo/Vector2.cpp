
#include "Vector2.h"

#include <cassert>
#include <cstring>
#include <cmath>

namespace pkzo
{
    Vector2::Vector2()
    {
        std::memset(data, 0, 2 * sizeof(float));        
    }

    Vector2::Vector2(float v)
    {
        data[0] = v;
        data[1] = v;
    }

    Vector2::Vector2(float x, float y)
    {
        data[0] = x;
        data[1] = y;
    }

    Vector2::Vector2(const Vector2& other)
    {
        std::memcpy(data, other.data, 2 * sizeof(float));
    }

    Vector2::~Vector2() {}

    const Vector2& Vector2::operator = (const Vector2& other)
    {
        std::memcpy(data, other.data, 2 * sizeof(float));
        return *this;
    }

    const Vector2& Vector2::operator += (const Vector2& other)
    {
        data[0] += other.data[0];
        data[1] += other.data[1];
        return *this;
    }

    const Vector2& Vector2::operator -= (const Vector2& other)
    {
        data[0] -= other.data[0];
        data[1] -= other.data[1];
        return *this;
    }

    float& Vector2::operator [] (unsigned int i)
    {
        assert(i < 2);
        return data[i];
    }

    float Vector2::operator [] (unsigned int i) const
    {
        assert(i < 2);
        return data[i];
    }

    Vector2::operator const float* () const
    {
        return data;
    }
    
    Vector2 operator + (const Vector2& a, const Vector2& b)
    {
        Vector2 t = a;
        t += b;
        return t;
    }
    
    Vector2 operator - (const Vector2& a, const Vector2& b)
    {
        Vector2 t = a;
        t -= b;
        return t;
    }
    
    Vector2 operator * (const Vector2& v, float s)
    {
        return Vector2(v[0] * s, v[1] * s);
    }
    
    Vector2 operator * (float s, const Vector2& v)
    {
        return v * s;
    }
    
    float dot(const Vector2& a, const Vector2& b)
    {
        return a[0] * b[0] + a[1] * b[1];
    }
    
    float length(Vector2& v)
    {
        return std::sqrt(dot(v, v));
    }
    
    Vector2 normalize(Vector2& v)
    {
        return v * (1 / length(v));
    }
}
