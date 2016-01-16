
#include <sstream>
#include <pkzo/Engine.h>

#include "TestScreen.h"

int main(int argc, char* argv[])
{
    pkzo::Engine engine("pkzo-interface");
    engine.switch_screen(new ui::TestScreen(engine));
    engine.run();
}
