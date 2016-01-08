
#include "HelloScreen.h"

#include <pkzo/Window.h>
#include <pkzo/Library.h>

#include "HelloEngine.h"

namespace hello
{
    HelloScreen::HelloScreen(HelloEngine& engine)
    : Screen(engine.get_window().get_width(), engine.get_window().get_height())
    {
        //pkzo::Text text;
        pkzo::Library& lib = engine.get_library();

        text.set_text("Hello World!");
        text.set_font(lib.load_font("../assets/fonts/DejaVuSans.ttf", 50));
        text.set_color(pkzo::Color(0x000000FF));
        text.set_position(get_width() / 2 - text.get_width() / 2, get_height() / 2 - text.get_height() / 2);
        add_widget(text);

    }

    HelloScreen::~HelloScreen() {}
}