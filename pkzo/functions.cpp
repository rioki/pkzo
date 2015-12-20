
#include "pkzo.h"

namespace pkzo
{
    std::function<void()> quit_cb;

    std::string get_version()
    {
        return PZKO_VERSION;
    }

    void route_events()
    {
        // stuff
        quit_cb();
    }

    void on_quit(std::function<void()> cb)
    {
        quit_cb = cb;
    }
}