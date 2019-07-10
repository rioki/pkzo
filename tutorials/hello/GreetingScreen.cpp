// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "GreetingScreen.h"

#include <pkzo/Rectangle.h>
#include <pkzo/Text.h>
#include <pkzo/Material.h>
#include <pkzo/Font.h>

namespace hello
{
    GreetingScreen::GreetingScreen(const glm::vec2& size)
    : Screen(size)
    {
        auto font = std::make_shared<pkzo::Font>("../data/fonts/DejaVuSans.ttf", 52);
        auto white = std::make_shared<pkzo::Material>("../data/materials/TextWhite.pxm");
        auto hello_text = std::make_shared<pkzo::Text>(glm::vec2{0.0f, 150.0f}, "Hello", font, white);
        add_node(hello_text);

        auto logo = std::make_shared<pkzo::Material>("../data/materials/PkzoLogo.pxm");
        auto rectangle = std::make_shared<pkzo::Rectangle>(glm::vec2{0.0f}, glm::vec2(395.0f, 117.0f), logo);
        add_node(rectangle);
    }
}
