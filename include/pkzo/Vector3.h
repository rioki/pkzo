
#ifndef _PKZO_VECTOR3_H_
#define _PKZO_VECTOR3_H_

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Vector3
    {
    public:
        Vector3();

        Vector3(float v);

        Vector3(float x, float y, float z);

        Vector3(const Vector3& other);

        ~Vector3();

        const Vector3& operator = (const Vector3& other);

        const Vector3& operator += (const Vector3& other);

        const Vector3& operator -= (const Vector3& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        const float* carray() const;

    private:
        float data[3];
    };

    PKZO_EXPORT
    Vector3 operator - (const Vector3& v);

    PKZO_EXPORT
    Vector3 operator + (const Vector3& a, const Vector3& b);

    PKZO_EXPORT
    Vector3 operator - (const Vector3& a, const Vector3& b);

    PKZO_EXPORT
    Vector3 operator * (const Vector3& v, float s);

    PKZO_EXPORT
    Vector3 operator * (float s, const Vector3& v);

    PKZO_EXPORT
    float dot(const Vector3& a, const Vector3& b);

    PKZO_EXPORT
    Vector3 cross(const Vector3& a, const Vector3& b);

    PKZO_EXPORT
    float length(Vector3& v);

    PKZO_EXPORT
    Vector3 normalize(Vector3& v);
}

#endif
