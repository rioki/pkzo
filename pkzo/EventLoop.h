// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
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

#ifndef _PKZO_EVENT_LOOP_H_
#define _PKZO_EVENT_LOOP_H_

#include <memory>

#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"

namespace pkzo
{
    /**
     * System Event Loop
     * 
     * The EventLoop serves as central mechanic to distribute system events.
     **/
    class PKZO_EXPORT EventLoop
    {
    public:
        
        EventLoop();

        EventLoop(const EventLoop&) = delete; 

        ~EventLoop();

        EventLoop& operator = (const EventLoop&) = delete;

        /**
         * Create a Window
         *
         * This function create a system window with the given size.
         *
         * @param width the window width
         * @param height the window height
         * @param fullscreen flag if the window is fullscreen
         **/
        std::shared_ptr<Window> open_window(unsigned int width, unsigned int height, bool fullscreen = false);

        /**
         * Get the Root Window
         *
         * This function returns the root window.
         **/
        std::shared_ptr<Window> get_window();

        /**
         * Get the Mouse
         **/
        std::shared_ptr<Mouse> get_mouse();

        /**
         * Get the Keyboard
         **/
        std::shared_ptr<Keyboard> get_keyboard();

        void tick();

        void run();

        void stop();

    private:
        bool                      running;
        std::shared_ptr<Window>   window;
        std::shared_ptr<Mouse>    mouse;
        std::shared_ptr<Keyboard> keyboard;

        void route_events();
    };
}

#endif
