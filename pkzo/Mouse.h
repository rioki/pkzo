// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include "defines.h"
#include "EventEmitter.h"

union SDL_Event;

namespace pkzo
{
    /*!
     * The Mouse
     */
    class PKZO_EXPORT Mouse : public EventEmitter
    {
    public:

        /*!
         * Events emited by the keyboard.
         */
        enum Event
        {
            BUTTON_PRESS,      //!< A button is pressed. void(uint button, uvec2 pos)
            BUTION_RELEASE,    //!< A button is released. void(uint button, uvec2 pos)
            MOVE               //!< The mouse is moved void(ivec2 rel, uvec2 pos)
        };

        Mouse();
        Mouse(const Mouse&) = delete;
        ~Mouse();
        const Mouse& operator = (const Mouse&) = delete;

        /*!
         * Show the cursor.
         */
        void show_cursor();
    
        /*!
         * Hide the cursor.
         */
        void hide_cursor();
        
        /*!
         * Check if the cursor is visible.
         *
         * @return true if the cursor is visible
         */
        bool is_cursor_visible() const;    

        /*!
         * Check if a mouse button is pressed.
         *
         * @param button the button to querry
         * @return true if the button is pressed
         */
        bool is_pressed(unsigned int button) const;

    private:
        void handle_event(SDL_Event& event);
        
		friend class Engine;
    };
}

#endif
