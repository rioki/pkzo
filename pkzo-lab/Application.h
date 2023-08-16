// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <atomic>
#include <pkzo/debug.h>
#include <pkzo/EventRouter.h>
#include <pkzo/Window.h>
#include <pkzo/Mouse.h>
#include <pkzo/Keyboard.h>
#include <pkzo-imgui/Interface.h>

namespace lab
{
    class Application
    {
    public:
        Application();

        int run();

        void stop();

    private:
        std::atomic<bool>  running       = false;
        pkzo::CrashHandler crash_handler;
        pkzo::EventRouter  event_router;
        pkzo::Window       window        = {event_router, {800, 600}, "pkzo lab"};
        pkzo::Mouse        mouse         = {event_router};
        pkzo::Keyboard     keyboard      = {event_router};

        pkzo::imgui::Interface debug_interface;

        void tick();
    };
}
