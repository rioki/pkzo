// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "MaterialsEngine.h"

int main(int argc, char* argv[])
{
    try
    {
        auto engine = mats::MaterialsEngine{};
        return engine.run();
    }
    catch (const std::exception& ex)
    {
        pkzo::show_error_dialog("Exception", ex.what());
        return -1;
    }
}
