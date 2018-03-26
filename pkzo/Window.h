// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
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

#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include <functional>
#include <vector>

#include <rgm/rgm.h>

#include "defines.h"
#include "SDLSentry.h"

typedef struct SDL_Window SDL_Window;
typedef void *SDL_GLContext;
union SDL_Event;

namespace pkzo
{
    
    class PKZO_EXPORT Window
    {
    public:
        
        enum Mode
        {
            STATIC,            
            RESIZABLE,
            FULLSCREEN
        };

        Window(rgm::ivec2 size, Mode mode = STATIC);

        Window(const Window&) = delete;

        ~Window();

        const Window& operator = (const Window&) = delete;

       rgm::ivec2 get_size() const;

        /**
         * Get the window's aspect ratio.
         **/
        float get_aspect() const;

        Mode get_mode() const;

        void on_draw(std::function<void ()> cb);

        void on_resize(std::function<void (rgm::ivec2)> cb);

        void on_close(std::function<void ()> cb);

        void draw();
        
    private:
        static std::vector<Window*> instances;

        SDLSentry sdl_sentry;

        SDL_Window*   window;
        SDL_GLContext glcontext;  
        
        Mode mode;  

        std::function<void ()>      draw_cb; 
        std::function<void (rgm::ivec2)> resize_cb;
        std::function<void ()>      close_cb;

        bool handle_event(SDL_Event& event);
           
    friend PKZO_EXPORT void route_events();
    friend class EventLoop;
    };
}

#endif
