
#ifndef _PKZO_QUATERNION_H_
#define _PKZO_QUATERNION_H_

#include "defines.h"

namespace pkzo
{
    class Vector3;

    class PKZO_EXPORT Quaternion
    {
    public:
        Quaternion();

        Quaternion(float x, float y, float z, float w);

        Quaternion(const Quaternion& other);

        ~Quaternion();

        const Quaternion& operator = (const Quaternion& other);

        const Quaternion& operator += (const Quaternion& other);

        const Quaternion& operator -= (const Quaternion& other);

        const Quaternion& operator *= (const Quaternion& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        operator const float* () const;

    private:
        float data[4];
    };

    PKZO_EXPORT
    Quaternion operator + (const Quaternion& a, const Quaternion& b);

    PKZO_EXPORT
    Quaternion operator - (const Quaternion& a, const Quaternion& b);

    PKZO_EXPORT
    Quaternion operator * (const Quaternion& a, const Quaternion& b);

    PKZO_EXPORT
    Quaternion normalize(const Quaternion& q);  

    PKZO_EXPORT
    Quaternion inverse(const Quaternion& q);

    PKZO_EXPORT
    Vector3 transform(const Quaternion& q, const Vector3& v);
}

#endif
