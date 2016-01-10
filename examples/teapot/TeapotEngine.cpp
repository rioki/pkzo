
#include "TeapotEngine.h"

#include <pkzo/Window.h>

#include "TeapotScreen.h"

namespace teapot
{
    TeapotEngine::TeapotEngine()
    : Engine("pkzo-teapot")
    {
        switch_screen(new TeapotScreen(pkzo::Vector2(get_window().get_width(), get_window().get_height()), get_library()));
    }

    TeapotEngine::~TeapotEngine()
    {

    }
}