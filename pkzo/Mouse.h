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

#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include "EventEmitter.h"

union SDL_Event;

namespace pkzo
{
    /**
     * Mouse
     *
     * @todo scroll events 
     **/
	class PKZO_EXPORT Mouse : public EventEmitter
    {
    public:
        
        enum Events
        {
            MOVE,
            BUTTON_PRESS,
            BUTTON_RELEASE
        };

        /**
         * Create a Mouse
         **/
        Mouse(); 
        
        Mouse(const Mouse&) = delete;

        /**
         * Destroy a Mouse
         **/
        ~Mouse();

        const Mouse& operator = (const Mouse&) = delete;
        
        /**
         * Check if a Button is Pressed
         *
         * @param button the number of button (1: left, 2: middle 3: right)
         *
         * @returns true if the button is pressed
         **/
        bool is_pressed(unsigned int button) const;

        /**
         * Get the Current Cursor Position
         *
         * @returns a tuple containing the x and y positions of the cursor
         **/
        std::tuple<unsigned int, unsigned int> get_cursor() const;
        
        /**
         * Show the Mouse Cursor
         **/
        void show_cursor();

        /**
         * Hide the Mouse Cursor
         **/        
        void hide_cursor();
        
        /**
         * Check if the Mouse Cursor is Visible
         **/
        bool is_cursor_visible() const;
        
    private:                
        void handle_event(SDL_Event& event);
        		
        friend class Engine;
    };
}

#endif
