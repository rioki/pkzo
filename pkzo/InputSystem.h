// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_INPUT_SYSTEM_H_
#define _PKZO_INPUT_SYSTEM_H_

#include "System.h"
#include "SdlSentry.h"

namespace pkzo
{
    class Engine;
    class Mouse;
    class Keyboard;

    //! Input system
    class PKZO_EXPORT InputSystem : public System
    {
    public:
        InputSystem(Engine& engine);

        //! Get the mouse
        std::shared_ptr<Mouse> get_mouse();
        //! Get the keyboard.
        std::shared_ptr<Keyboard> get_keyboard();

        void tick(float dt) override;

    private:
        SdlSentry                 sdl_sentry;
        Engine&                   engine;
        std::shared_ptr<Mouse>    mouse;
        std::shared_ptr<Keyboard> keyboard;
    };
}

#endif
