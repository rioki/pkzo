// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_ENGINE_H_
#define _PKZO_ENGINE_H_

#include <memory>
#include <atomic>
#include <string>
#include <string_view>

#include "defines.h"
#include "stdex.h"

namespace pkzo
{
    class Window;
    class Mouse;
    class Keyboard;
    class Screen;
    class Scene;
    class Camera;
    class RenderQueue;

    /*!
     * Central object holding all the bits together.
     */
    class PKZO_EXPORT Engine : private stdex::non_copyable
    {
    public:
        /*!
         * Create engine.
         *
         * @param id the id of the engine
         * @param argc command line argument count
         * @param argv command line values
         */
        Engine(const std::string_view id);
        virtual ~Engine();

        /*!
         * The engine id.
         *
         * The engine id is used for many things, such as settings.
         */
        const std::string& get_id() const;

        /*!
         * The primary output window.
         *
         * @{
         */
        Window& get_window();
        const Window& get_window() const;
        /*! @} */

        /*!
         * The mouse.
         *
         * @{
         */
        Mouse& get_mouse();
        const Mouse& get_mouse() const;
        /*! @} */

        /*!
         * The keyboard.
         *
         * @{
         */
        Keyboard& get_keyboard();
        const Keyboard& get_keyboard() const;
        /*! @} */

        /*!
         * The overlay screen.
         * @{
         */
        void set_screen(std::shared_ptr<Screen> value);
        std::shared_ptr<Screen> get_screen() const;
        /*! @} */

        /*!
         * Scene
         * @{
         */
        void set_scene(std::shared_ptr<Scene> value);
        std::shared_ptr<Scene> get_scene() const;
        /*! @} */

        /*!
         * Camera
         * @{
         */
        void set_camera(std::shared_ptr<Camera> value);
        std::shared_ptr<Camera> get_camera() const;
        /*! @} */

        /*!
         * Main event loop.
         */
        int run();

        /*!
         * Break out of the main even loop.
         */
        void stop();

    protected:
        virtual void tick();

    private:
        std::string                  id;
        std::atomic<bool>            running;
        std::unique_ptr<Window>      window;
        std::unique_ptr<Mouse>       mouse;
        std::unique_ptr<Keyboard>    keyboard;
        std::unique_ptr<RenderQueue> render_queue;

        std::shared_ptr<Screen>      screen;
        std::shared_ptr<Scene>       scene;
        std::shared_ptr<Camera>      camera;

        void handle_events();
        void draw();
    };

    PKZO_EXPORT
    void show_error_dialog(const std::string_view caption, const std::string_view message);
}

#endif
