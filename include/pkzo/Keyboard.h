
#ifndef _PKZO_KEYBOARD_H_
#define _PKZO_KEYBOARD_H_

#include <vector>
#include <functional>

#include "defines.h"
#include "Key.h"

union SDL_Event;

namespace pkzo
{
    /**
     * Keyboard
     **/
	class PKZO_EXPORT Keyboard
    {
    public:
        /**
         * Construct a Keyboard
         **/
        Keyboard(); 
        
        Keyboard(const Keyboard&) = delete;

        /**
         * Destroy a Keyboard
         **/
        ~Keyboard();
        
        const Keyboard& operator = (const Keyboard&) = delete;    
    
        /**
         * Check if a specific key is pressed.
         *
         * @param key the key to query
         *
         * @returns true if the given key is currently pressed
         **/
        bool is_pressed(Key key) const;
    
        /**
         * Install key press event handler.
         **/
        void on_key_press(std::function<void (Key)> cb);
        
        /**
         * Install key release event handler.
         **/
        void on_key_release(std::function<void (Key)> cb);
        
        /**
         * Install text event handler.
         **/
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
