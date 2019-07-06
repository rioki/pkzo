// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_KEYBOARD_H_
#define _PKZO_KEYBOARD_H_

#include "defines.h"
#include "EventEmitter.h"
#include "Key.h"

union SDL_Event;

namespace pkzo
{
    /*!
     * Keyboard
     */
	class PKZO_EXPORT Keyboard : public EventEmitter
    {
    public:
        
        /*!
         * Events emited by the keyboard.
         */
        enum Event
        {
            KEY_PRESS,      //!< A key is pressed. void(Key key)
            KEY_RELEASE,    //!< A key is released. void(Key key)
            TEXT            //!< The textual represntation of key storkes. void(string_view text)
        };

        Keyboard(); 
        Keyboard(const Keyboard&) = delete;
        ~Keyboard();    
        const Keyboard& operator = (const Keyboard&) = delete;
        
        /*!
         * Check if a given key is pressed.
         *
         * @param key
         * @return true if the key is pressed
         */
        bool is_pressed(Key key) const;
        
    private:               
        void handle_event(SDL_Event& event);
        
		friend class Engine;
    };
}

#endif
