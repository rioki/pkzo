// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "HelloEngine.h"

#include <pkzo/Window.h>

#include "GreetingScreen.h"

namespace hello
{
    HelloEngine::HelloEngine()
    : Engine{"Hello"}
    {
        auto screen = std::make_shared<GreetingScreen>(glm::vec2(get_window()->get_size()));
        set_screen(screen);
    }
}
