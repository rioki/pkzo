
#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include <functional>

#include "defines.h"

union SDL_Event;
typedef struct SDL_Window SDL_Window;
typedef void *SDL_GLContext;

namespace pkzo
{
    /**
     * Window
     *
     * The window is the primary graphical output context.
     **/
    class PKZO_EXPORT Window
    {
    public:
        enum Flags
        {
            NO_FLAGS = 0,
            FULLSCREEN = 0x01,
            BORDERLESS = 0x02,
            RESIZABLE = 0x04
        };

        /**
        * Create a new Window
        *
        * @param width the width of the window
        * @param height the height of the window
        * @param flags the creation flags, see @a Window::Flags
        *
        * @note If the size is (0,0) and fullscreen the window will be opened
        * in the native resolution.
        **/
        Window(unsigned int width, unsigned int height, Flags flags = NO_FLAGS);
        
        Window(const Window&) = delete;    

        ~Window();

        const Window& operator = (const Window&) = delete;

        /**
         * Redraw Event Handler
         **/
        void on_draw(std::function<void()> cb);

        /**
         * Redraw the window.
         **/
        void draw();

    private:
        SDL_Window*   window;
        SDL_GLContext glcontext;

        std::function<void ()> draw_cb;
    };

    inline
    Window::Flags operator | (Window::Flags a, Window::Flags b)
    {
        return (Window::Flags)((unsigned int)a | (unsigned int)b);
    }

    inline
    Window::Flags operator & (Window::Flags a, Window::Flags b)
    {
        return (Window::Flags)((unsigned int)a & (unsigned int)b);
    }

    inline
    Window::Flags operator ^ (Window::Flags a, Window::Flags b)
    {
        return (Window::Flags)((unsigned int)a ^ (unsigned int)b);
    }
}

#endif
