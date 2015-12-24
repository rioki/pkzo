//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#ifndef _PKZO_FUNCTION_H_
#define _PKZO_FUNCTION_H_

#include <string>
#include <functional>

#include "defines.h"

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
    void on_quit(std::function<void()> cb);
}

#endif
