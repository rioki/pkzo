/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <pkzo/pkzo.h>

int main(int argc, char* argv[])
{    
    bool running = true;                        // flag used to control the main loop

    pkzo::Window window(rgm::ivec2(1280, 768)); // open a window for rendering
    window.on_draw([&] () {                     // when the window is drawn, this callback is called
        // all rendering code goes here
    });
    window.on_close([&] () {                    // handle ALT+F4 and window X events
        running = false;
    });

    pkzo::Keyboard keyboard;                    // keyboard 
    keyboard.on_key_press([&] (pkzo::Key key) { // on key press event
        if (key == pkzo::KEY_ESCAPE)            // check if ESC then also stop execution,                
        {                                       // this is done to handle the fullscreen situation
            running = false;                    // where no ALT+F4 and window X events are emitted
        }
    });    

    while (running)                             // main loop
    {
        pkzo::route_events();                   // route OS events the the apropriate handlers
        // update game logic here
        window.draw();                          // trigger window redraw 
    }
}
