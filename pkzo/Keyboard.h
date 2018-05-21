/*
  pkzo

  Copyright (c) 2014-2017 Sean Farrell

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

#ifndef _PKZO_KEYBOARD_H_
#define _PKZO_KEYBOARD_H_

#include <vector>
#include <functional>

#include "defines.h"
#include "Key.h"

union SDL_Event;

namespace pkzo
{
	class PKZO_EXPORT Keyboard
    {
    public:
        Keyboard(); 
        
        Keyboard(const Keyboard&) = delete;

        ~Keyboard();    

        const Keyboard& operator = (const Keyboard&) = delete;
    
        bool is_pressed(Key key) const;
    
        void on_key_press(std::function<void (Key)> cb);
        
        void on_key_release(std::function<void (Key)> cb);
        
        void on_text(std::function<void (std::string)> cb);
        
    private:
        static std::vector<Keyboard*> instances;
        
        std::function<void (Key)> key_press_cb;
        std::function<void (Key)> key_release_cb;
        std::function<void (std::string)> text_cb;
                
        void handle_event(SDL_Event& event);
        
		friend PKZO_EXPORT void route_events();
    };
}

#endif
