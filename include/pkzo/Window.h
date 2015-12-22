
#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include <functional>
#include <string>

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
        /**
         * Window Creation Flags
         **/
        enum Flags
        {
            NO_FLAGS   = 0,    //!< No flags
            FULLSCREEN = 0x01, //!< Fullscreen
            BORDERLESS = 0x02, //!< Borderless
            RESIZABLE  = 0x04  //!< Resizable
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

        /**
         * Close a Window
         **/
        ~Window();

        const Window& operator = (const Window&) = delete;

        /**
         * Set the Window's Title Caption
         *
         * @param value the window title caption
         **/
        void set_title(const std::string& value);

        /**
         * Get the Window's Title Caption
         *
         * @return the window title caption
         **/
        std::string get_title() const;

        /**
         * Redraw Event Handler
         * 
         * This function installs the drawing callback used by Window::draw().
         *
         * @param cb the callback
         **/
        void on_draw(std::function<void()> cb);

        /**
         * Redraw the Window.
         *
         * This function will make the OpenGL graphic context valid and call the 
         * draw callback. Within the callback a valid graphic context exists and
         * it is safe to call OpenGL functions. 
         *
         * @note pkzo uses GLEW to access OpenGL functions, it is safe to use
         * GLEW wrapped function without calling glewInit(). 
         *
         * @see Window::on_draw
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
