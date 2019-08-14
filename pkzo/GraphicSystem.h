// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_GRAPHIC_SYSTEM_H_
#define _PKZO_GRAPHIC_SYSTEM_H_

#include "System.h"
#include "SdlSentry.h"

namespace pkzo
{
    class Engine;
    class Window;
    class RenderQueue;

    //! Input system
    class PKZO_EXPORT GraphicSystem : public System
    {
    public:
        GraphicSystem(Engine& engine);
        ~GraphicSystem();

        //! Get the window
        std::shared_ptr<Window> get_window();

        void tick(float dt) override;

    private:
        SdlSentry                    sdl_sentry;
        Engine&                      engine;
        std::shared_ptr<Window>      window;
        std::unique_ptr<RenderQueue> render_queue;

        void draw();
    };
}

#endif
