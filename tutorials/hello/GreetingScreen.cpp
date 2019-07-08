// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "GreetingScreen.h"

#include <pkzo/Rectangle.h>
#include <pkzo/Material.h>

namespace hello
{
    GreetingScreen::GreetingScreen(const glm::vec2& size)
    : Screen(size)
    {
        auto white = std::make_shared<pkzo::Material>("../data/materials/PkzoLogo.pxm");
        auto recangle = std::make_shared<pkzo::Rectangle>(glm::vec2{0.0f}, glm::vec2(395.0f, 117.0f), white);
        add_node(recangle);
    }
}
