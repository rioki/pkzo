
#ifndef _TEAPOT_SCREEN_H_
#define _TEAPOT_SCREEN_H_

#include <pkzo/Screen.h>
#include <pkzo/Text.h>
#include <pkzo/Vector2.h>
#include <pkzo/Library.h>

namespace teapot
{
    class TeapotScreen : public pkzo::Screen
    {
    public:
        
        TeapotScreen(const pkzo::Vector2& size, pkzo::Library& library);

        ~TeapotScreen();

    private:
        pkzo::Text caption;
        pkzo::Text explanation;
    };

}

#endif