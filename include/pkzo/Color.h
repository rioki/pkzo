
#ifndef _PKZOUI_COLOR_H_
#define _PKZOUI_COLOR_H_

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Color
    {
    public:
        
        Color();

        Color(unsigned long hex);

        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

        Color(float r, float g, float b, float a = 1.0f);

        Color(const Color& other);

        ~Color();
        
        const Color& operator = (const Color& other);

        float& operator [] (unsigned int i);

        float operator [] (unsigned int i) const;

        operator const float* () const;
        
    private:
        float values[4];
    };
}

#endif
