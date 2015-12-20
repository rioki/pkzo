
#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include "defines.h"

namespace pkzo
{
    class PKZO_EXPORT Window
    {
    public:
        Window(unsigned int width, unsigned int height, bool fullscreen);
        
        Window(const Window&) = delete;    

        ~Window();

        const Window& operator = (const Window&) = delete;

        void draw();

    private:
    };
}

#endif
