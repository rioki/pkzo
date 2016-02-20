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
#include <pkzo2d/pkzo2d.h>

#include "TestScreen.h"

int main(int argc, char* argv[])
{    
    bool  running = true;
        
    pkzo::Window window(rgm::ivec2(1280, 768));  
    pkzo::Canvas canvas(window.get_size());
    ui::TestScreen screen(window.get_size());

    window.on_draw([&] () {                     
        screen.draw(canvas);
    });
    window.on_close([&] () {                    
        running = false;
    });

    pkzo::Keyboard keyboard;                    
    keyboard.on_key_press([&] (pkzo::Key key) { 
        if (key == pkzo::KEY_ESCAPE)            
        {                                       
            running = false;                    
        }
    });    

    pkzo::Mouse mouse;
    mouse.on_move([&] (rgm::ivec2 mov, rgm::ivec2 pos) {
        screen.handle_mouse_move(mov, pos);
    });
    mouse.on_button_press([&] (unsigned int button, rgm::ivec2 pos) {
        screen.handle_mouse_press(button, pos);
    });
    mouse.on_button_release([&] (unsigned int button, rgm::ivec2 pos) {
        screen.handle_mouse_release(button, pos);
    });

    while (running)                             
    {
        pkzo::route_events();                   
        
        window.draw();                          
    }
}
