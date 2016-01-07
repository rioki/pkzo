
#ifndef _PKZO_VECTOR4_H_
#define _PKZO_VECTOR4_H_

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Vector4
    {
    public:
        Vector4();

        Vector4(float v);

        Vector4(float x, float y, float z, float m);

        Vector4(const Vector4& other);

        ~Vector4();

        const Vector4& operator = (const Vector4& other);

        const Vector4& operator += (const Vector4& other);

        const Vector4& operator -= (const Vector4& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        const float* carray() const;

    private:
        float data[4];
    };

    PKZO_EXPORT
    Vector4 operator - (const Vector4& v);

    PKZO_EXPORT
    Vector4 operator + (const Vector4& a, const Vector4& b);

    PKZO_EXPORT
    Vector4 operator - (const Vector4& a, const Vector4& b);

    PKZO_EXPORT
    Vector4 operator * (const Vector4& v, float s);

    PKZO_EXPORT
    Vector4 operator * (float s, const Vector4& v);

    PKZO_EXPORT
    float dot(const Vector4& a, const Vector4& b);

    PKZO_EXPORT
    float length(const Vector4& v);

    PKZO_EXPORT
    Vector4 normalize(const Vector4& v);
}

#endif
