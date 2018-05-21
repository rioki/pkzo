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

#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include <functional>
#include <vector>
#include <rgm/rgm.h>

#include "defines.h"

union SDL_Event;

namespace pkzo
{
    class PKZO_EXPORT Mouse
    {
    public:
        Mouse();

        Mouse(const Mouse&) = delete;

        ~Mouse();

        const Mouse& operator = (const Mouse&) = delete;

        void on_move(std::function<void (rgm::uvec2, rgm::ivec2)> cb);

        void on_button_press(std::function<void (unsigned int, rgm::uvec2)> cb);

        void on_button_release(std::function<void (unsigned int, rgm::uvec2)> cb);

        void show_cursor();
    
        void hide_cursor();
        
        bool is_cursor_visible() const;    

        /**
         * Check if a mouse button is pressed.
         **/
        bool is_pressed(unsigned int button) const;

    private:
        static std::vector<Mouse*> instances;

        std::function<void (rgm::uvec2, rgm::ivec2)>   move_cb;
        std::function<void (unsigned int, rgm::uvec2)> button_press_cb;
        std::function<void (unsigned int, rgm::uvec2)> button_release_cb;

        void handle_event(SDL_Event& event);
        
		friend PKZO_EXPORT void route_events();
    };
}

#endif
