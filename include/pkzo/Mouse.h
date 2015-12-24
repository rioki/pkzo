
#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include <vector>
#include <functional>

#include "defines.h"

union SDL_Event;

namespace pkzo
{
    /**
     * Mouse
     *
     * @todo scroll events 
     **/
	class PKZO_EXPORT Mouse
    {
    public:
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
         * Install the Button Press Event Handler
         **/
        void on_button_press(std::function<void (unsigned int, unsigned int, unsigned int)> cb);
        
        /**
         * Install the Button Release Event Handler
         **/
        void on_button_release(std::function<void (unsigned int, unsigned int, unsigned int)> cb);
        
        /**
         * Install the Mouse Move Event Handler
         **/
        void on_move(std::function<void (unsigned int, unsigned int, int, int)> cb);
        
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
        static std::vector<Mouse*> instances;
        
        std::function<void (unsigned int, unsigned int, unsigned int)> button_press_cb;        
        std::function<void (unsigned int, unsigned int, unsigned int)> button_release_cb;        
        std::function<void (unsigned int, unsigned int, int, int)> move_cb;
        
        void handle_event(SDL_Event& event);
        
		friend PKZO_EXPORT void route_events();
    };
}

#endif
