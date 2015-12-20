
#ifndef _PKZO_H_
#define _PKZO_H_

#include <string>
#include <functional>

#include "pkzo/defines.h"
#include "pkzo/Window.h"

namespace pkzo
{
    /**
     * Initialized third party components.
     *
     * You don't need to call this function, it will be called for you.
     **/
    PKZO_EXPORT
    void init();
    
    /**
     * Get the version linked library.
     *
     * @return the linked version
     **/
    PKZO_EXPORT
    std::string get_version();

    /** 
     * Route system events.
     * 
     * This function routes the system events to the apropriate 
     * objects. It is expected that you call this function periodically
     * from the main thread.
     **/
    PKZO_EXPORT
    void route_events();

    /**
     * Hook the quit event.
     *
     * The quit event is called when the application (main window) recives
     * a quit or close event. This is normally what happens when the user
     * clicks the "X" on the window or ALT+F4.
     **/
    PKZO_EXPORT
    void on_quit(std::function<void ()> cb);
}

#endif
