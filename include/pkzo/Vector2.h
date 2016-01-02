
#ifndef _PKZO_VECTOR2_H_
#define _PKZO_VECTOR2_H_

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Vector2
    {
    public:
        Vector2();

        Vector2(float v);

        Vector2(float x, float y);

        Vector2(const Vector2& other);

        ~Vector2();

        const Vector2& operator = (const Vector2& other);

        const Vector2& operator += (const Vector2& other);

        const Vector2& operator -= (const Vector2& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        operator const float* () const;

    private:
        float data[2];
    };

    PKZO_EXPORT
    Vector2 operator - (const Vector2& v);

    PKZO_EXPORT
    Vector2 operator + (const Vector2& a, const Vector2& b);

    PKZO_EXPORT
    Vector2 operator - (const Vector2& a, const Vector2& b);

    PKZO_EXPORT
    Vector2 operator * (const Vector2& v, float s);

    PKZO_EXPORT
    Vector2 operator * (float s, const Vector2& v);

    PKZO_EXPORT
    float dot(const Vector2& a, const Vector2& b);

    PKZO_EXPORT
    float length(Vector2& v);

    PKZO_EXPORT
    Vector2 normalize(Vector2& v);
}

#endif
