// hello.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <pkzo/pkzo.h>

int main(int argc, char* argv[])
{
    try
    {
        auto engine = pkzo::Engine{"Hello", argc, argv};
        return engine.run();
    }
    catch (const std::exception& ex)
    {
        pkzo::show_error_dialog("Exception", ex.what());
        return -1;
    }
}
