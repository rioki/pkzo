
#include "Matrix3.h"

#include <cassert>
#include <cstring>
#include <cmath>

#include "Vector3.h"
#include "Matrix4.h"

namespace pkzo
{
    Matrix3::Matrix3()
    {
        std::memset(data, 0, 9 * sizeof(float));
        data[0] = 1.0f;
        data[4] = 1.0f;
        data[8] = 1.0f;
    }

    Matrix3::Matrix3(float v)
    {
        std::memset(data, 0, 9 * sizeof(float));
        data[0] = v;
        data[4] = v;
        data[8] = v;
    }

    Matrix3::Matrix3(float v0, float v3, float v6,
                     float v1, float v4, float v7,
                     float v2, float v5, float v8)
    {
        data[0] = v0;
        data[1] = v1;
        data[2] = v2;
        data[3] = v3;
        data[3] = v3;
        data[5] = v5;
        data[6] = v6;
        data[7] = v7;
        data[8] = v8;
    }

    Matrix3::Matrix3(const Matrix4& m4)
    {
        data[0] = m4[0];
        data[1] = m4[1];
        data[2] = m4[2];
        data[3] = m4[4];
        data[3] = m4[5];
        data[5] = m4[6];
        data[6] = m4[8];
        data[7] = m4[9];
        data[8] = m4[10];
    }

    Matrix3::Matrix3(const Matrix3& other)
    {
        std::memcpy(data, other.data, 9 * sizeof(float));
    }

    Matrix3::~Matrix3() {}

    const Matrix3& Matrix3::operator = (const Matrix3& other)
    {
        std::memcpy(data, other.data, 9 * sizeof(float));
        return *this;
    }

    const Matrix3& Matrix3::operator += (const Matrix3& other)
    {
        for (unsigned int i = 0; i < 9; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }

    const Matrix3& Matrix3::operator -= (const Matrix3& other)
    {
        for (unsigned int i = 0; i < 9; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }

    const Matrix3& Matrix3::operator *= (const Matrix3& other)
    {
        float tmp[9];

        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                float v = 0;
                for (unsigned int k = 0; k < 3; k++) {
                    v = v + data[i*3 + k] * other.data[k*3 + j];
                }
                tmp[i*3 + j] = v;
            }
        }
        
        std::memcpy(data, tmp, 9 * sizeof(float));

        return *this;
    }

    float& Matrix3::operator [] (unsigned int i)
    {
        assert(i < 9);
        return data[i];
    }

    float Matrix3::operator [] (unsigned int i) const
    {
        assert(i < 9);
        return data[i];
    }

    const float* Matrix3::carray() const
    {
        return data;
    }
    
    Matrix3 operator + (const Matrix3& a, const Matrix3& b)
    {
        Matrix3 t(a);
        t += b;
        return t;
    }

    Matrix3 operator - (const Matrix3& a, const Matrix3& b)
    {
        Matrix3 t(a);
        t -= b;
        return t;
    }
    
    Matrix3 operator * (const Matrix3& a, const Matrix3& b)
    {
        Matrix3 t(a);
        t *= b;
        return t;
    }
    
    Vector3 operator * (const Matrix3& m, const Vector3& v)
    {
        Vector3 r;

        r[0] = m[0] * v[0] + m[3] * v[1] + m[6] * v[2];
        r[1] = m[1] * v[0] + m[4] * v[1] + m[7] * v[2];
        r[2] = m[2] * v[0] + m[5] * v[1] + m[8] * v[2];

        return r;
    }

    PKZO_EXPORT
    Matrix3 transpose(const Matrix3& m)
    {
        Matrix3 r;
        for (unsigned int i = 0; i < 3; i++) {            
            for (unsigned int j = 0; j < 3; j++) {
                r[j*3 + i] = m[i*3 + j]; 
            }
        }
        return r;
    }

    Vector3 transform(const Matrix3& m, const Vector3& v)
    {
        return m * v;
    }
}
