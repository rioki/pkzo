
#include "Matrix4.h"

#include <cassert>
#include <cstring>
#include <cmath>

#include "Vector3.h"
#include "Vector4.h"

namespace pkzo
{
    Matrix4::Matrix4()
    {
        std::memset(data, 0, 16 * sizeof(float));
        data[0] = 1.0f;
        data[5] = 1.0f;
        data[10] = 1.0f;
        data[15] = 1.0f;
    }

    Matrix4::Matrix4(float v)
    {
        std::memset(data, 0, 16 * sizeof(float));
        data[0] = v;
        data[5] = v;
        data[10] = v;
        data[15] = v;
    }

    Matrix4::Matrix4(float v0, float v4, float  v8, float v12,
        float v1, float v5, float  v9, float v13,
        float v2, float v6, float v10, float v14,
        float v3, float v7, float v11, float v15)
    {
        data[0] = v0;
        data[1] = v1;
        data[2] = v2;
        data[3] = v3;
        data[4] = v4;
        data[5] = v5;
        data[6] = v6;
        data[7] = v7;
        data[8] = v8;
        data[9] = v9;
        data[10] = v10;
        data[11] = v11;
        data[12] = v12;
        data[13] = v13;
        data[14] = v14;
        data[15] = v15;
    }

    Matrix4::Matrix4(const Matrix4& other)
    {
        std::memcpy(data, other.data, 16 * sizeof(float));
    }

    Matrix4::~Matrix4() {}

    const Matrix4& Matrix4::operator = (const Matrix4& other)
    {
        std::memcpy(data, other.data, 16 * sizeof(float));
        return *this;
    }

    const Matrix4& Matrix4::operator += (const Matrix4& other)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }

    const Matrix4& Matrix4::operator -= (const Matrix4& other)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }

    const Matrix4& Matrix4::operator *= (const Matrix4& other)
    {
        float tmp[16];

        for (unsigned int i = 0; i < 4; i++) {
            for (unsigned int j = 0; j < 4; j++) {
                float v = 0;
                for (unsigned int k = 0; k < 4; k++) {
                    v = v + data[i*4 + k] * other.data[k*4 + j];
                }
                tmp[i*4 + j] = v;
            }
        }
        
        std::memcpy(data, tmp, 16 * sizeof(float));

        return *this;
    }

    float& Matrix4::operator [] (unsigned int i)
    {
        assert(i < 16);
        return data[i];
    }

    float Matrix4::operator [] (unsigned int i) const
    {
        assert(i < 16);
        return data[i];
    }

    const float* Matrix4::carray() const
    {
        return data;
    }
    
    Matrix4 operator + (const Matrix4& a, const Matrix4& b)
    {
        Matrix4 t(a);
        t += b;
        return t;
    }

    Matrix4 operator - (const Matrix4& a, const Matrix4& b)
    {
        Matrix4 t(a);
        t -= b;
        return t;
    }
    
    Matrix4 operator * (const Matrix4& a, const Matrix4& b)
    {
        Matrix4 t(a);
        t *= b;
        return t;
    }
    
    Vector4 operator * (const Matrix4& m, const Vector4& v)
    {
        Vector4 r;

        r[0] = m[0] * v[0] + m[4] * v[1] + m[ 8] * v[2] + m[12] * v[3];
        r[1] = m[1] * v[0] + m[5] * v[1] + m[ 9] * v[2] + m[13] * v[3];
        r[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
        r[2] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];

        return r;
    }

    PKZO_EXPORT
    Matrix4 transpose(const Matrix4& m)
    {
        Matrix4 r;
        for (unsigned int i = 0; i < 4; i++) {            
            for (unsigned int j = 0; j < 4; j++) {
                r[j*4 + i] = m[i*4 + j]; 
            }
        }
        return r;
    }

    Vector3 transform(const Matrix4& m, const Vector3& v)
    {
        Vector4 v4(v[0], v[1], v[2], 1.0f);
        Vector4 r = m * v4;
        return Vector3(r[0], r[1], r[2]);
    }
}
