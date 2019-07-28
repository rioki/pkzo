// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "GreetingScreen.h"

namespace hello
{
    GreetingScreen::GreetingScreen(const glm::vec2& size)
    : Screen(size)
    {
        auto solid_white_material = std::make_shared<pkzo::Material>("../data/materials/screen/MaskedSolidWhite.pxm");
        auto font = std::make_shared<pkzo::Font>("../data/fonts/DejaVuSans.ttf", 52);
        auto hello_text = std::make_shared<pkzo::Text>(glm::vec2{0.0f, 150.0f}, "Hello", font, solid_white_material);
        add_node(hello_text);

        auto logo_material = std::make_shared<pkzo::Material>("../data/materials/screen/PkzoLogo.pxm");
        auto logo = std::make_shared<pkzo::Rectangle>(glm::vec2{0.0f}, glm::vec2{395.0f, 117.0f}, logo_material);
        add_node(logo);
    }
}
