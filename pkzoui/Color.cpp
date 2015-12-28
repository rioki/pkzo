
#include "Color.h"

#include <cstring>

namespace pkzoui
{        
    Color::Color()
    {
        values[0] = 1.0f;
        values[1] = 1.0f;
        values[2] = 1.0f;
        values[3] = 1.0f;
    }

    Color::Color(unsigned long hex)
    {
        unsigned char r = (0xFF000000 & hex) >> 24;
        unsigned char g = (0x00FF0000 & hex) >> 16;
        unsigned char b = (0x0000FF00 & hex) >> 8;
        unsigned char a = (0x000000FF & hex);  

        values[0] = static_cast<float>(r) / 256.0f;
        values[1] = static_cast<float>(g) / 256.0f;
        values[2] = static_cast<float>(b) / 256.0f;
        values[3] = static_cast<float>(a) / 256.0f;
    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        values[0] = static_cast<float>(r) / 256.0f;
        values[1] = static_cast<float>(g) / 256.0f;
        values[2] = static_cast<float>(b) / 256.0f;
        values[3] = static_cast<float>(a) / 256.0f;
    }

    Color::Color(float r, float g, float b, float a)
    {
        values[0] = r;
        values[1] = g;
        values[2] = b;
        values[3] = a;
    }

    Color::Color(const Color& other)
    {
        std::memcpy(values, other.values, 4 * sizeof(float));
    }

    Color::~Color() {}
        
    const Color& Color::operator = (const Color& other)
    {
        std::memcpy(values, other.values, 4 * sizeof(float));
        return *this;
    }

    float Color::r() const
    {
        return values[0];
    }

    float Color::g() const
    {
        return values[1];
    }

    float Color::b() const
    {
        return values[2];
    }

    float Color::a() const
    {
        return values[3];
    }

    Color::operator const float* () const
    {
        return values;
    }

}
