
#ifndef _PKZO_MATRIX4_H_
#define _PKZO_MATRIX4_H_

#include "defines.h"

namespace pkzo
{
    class Vector3;
    class Vector4;

    class PKZO_EXPORT Matrix4 
    {
    public:

        Matrix4();

        Matrix4(float v);

        Matrix4(float v0, float v4, float  v8, float v12,
                float v1, float v5, float  v9, float v13,
                float v2, float v6, float v10, float v14,
                float v3, float v7, float v11, float v15);

        Matrix4(const Matrix4& other);

        ~Matrix4();

        const Matrix4& operator = (const Matrix4& other);

        const Matrix4& operator += (const Matrix4& other);

        const Matrix4& operator -= (const Matrix4& other);

        const Matrix4& operator *= (const Matrix4& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        const float* carray() const;

    private:
        float data[16];
    };

    PKZO_EXPORT
    Matrix4 operator + (const Matrix4& a, const Matrix4& b);

    PKZO_EXPORT
    Matrix4 operator - (const Matrix4& a, const Matrix4& b);

    PKZO_EXPORT
    Matrix4 operator * (const Matrix4& a, const Matrix4& b);

    PKZO_EXPORT
    Vector4 operator * (const Matrix4& m, const Vector4& v);

    PKZO_EXPORT
    Vector3 transform(const Matrix4& m, const Vector3& v);
}

#endif
