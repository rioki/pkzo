
#ifndef _PKZO_MATRIX3_H_
#define _PKZO_MATRIX3_H_

#include "defines.h"

namespace pkzo
{
    class Vector3;
    class Matrix4;

    class PKZO_EXPORT Matrix3 
    {
    public:

        Matrix3();

        Matrix3(float v);

        Matrix3(float v0, float v3, float v6,
                float v1, float v4, float v7,
                float v2, float v5, float v8);

        Matrix3(const Matrix4& m4);

        Matrix3(const Matrix3& other);

        ~Matrix3();

        const Matrix3& operator = (const Matrix3& other);

        const Matrix3& operator += (const Matrix3& other);

        const Matrix3& operator -= (const Matrix3& other);

        const Matrix3& operator *= (const Matrix3& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        const float* carray() const;

    private:
        float data[9];
    };

    PKZO_EXPORT
    Matrix3 operator + (const Matrix3& a, const Matrix3& b);

    PKZO_EXPORT
    Matrix3 operator - (const Matrix3& a, const Matrix3& b);

    PKZO_EXPORT
    Matrix3 operator * (const Matrix3& a, const Matrix3& b);

    PKZO_EXPORT
    Vector3 operator * (const Matrix3& m, const Vector3& v);

    PKZO_EXPORT
    Matrix3 transpose(const Matrix3& m);

    PKZO_EXPORT
    Vector3 transform(const Matrix3& m, const Vector3& v);
}

#endif
