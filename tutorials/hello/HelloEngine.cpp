// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "HelloEngine.h"

#include <pkzo/stdex.h>
#include <pkzo/Window.h>

#include "GreetingScreen.h"

namespace hello
{
    HelloEngine::HelloEngine()
    : Engine{"Hello"},
      screen{glm::vec2(get_window().get_size())}
    {
        set_screen(stdex::wrap_shared(screen));
    }
}
