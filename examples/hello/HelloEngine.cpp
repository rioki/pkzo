
#include "HelloEngine.h"

#include "HelloScreen.h"

namespace hello
{
    HelloEngine::HelloEngine()
    : Engine("pkzo-hello")
    {
        switch_screen(new HelloScreen(*this));
    }

    HelloEngine::~HelloEngine() {}
}