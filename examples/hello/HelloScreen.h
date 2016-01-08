
#ifndef _HELLO_SCREEN_H_
#define _HELLO_SCREEN_H_

#include <pkzo/Screen.h>
#include <pkzo/Text.h>

namespace hello
{
    class HelloEngine;

    class HelloScreen : public pkzo::Screen
    {
    public:
        HelloScreen(HelloEngine& engine);

        ~HelloScreen();

    private:
        pkzo::Text text;
    };
}

#endif
