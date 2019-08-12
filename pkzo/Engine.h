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
#include "EventEmitter.h"

namespace pkzo
{
    class Window;
    class Mouse;
    class Keyboard;
    class Screen;
    class Scene;
    class Camera;
    class RenderQueue;
    class System;

    /*!
     * Central object holding all the bits together.
     */
    class PKZO_EXPORT Engine : private stdex::non_copyable, public EventEmitter
    {
    public:
        enum EventId
        {
            CHANGE_SCENE,
            CHANGE_CAMERA
        };

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

        //! Get the mouse.
        std::shared_ptr<Mouse> get_mouse();
        //! Get the keyboard.
        std::shared_ptr<Keyboard> get_keyboard();

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

        //! Start a system.
        template <typename SystemT>
        void start_system();

        //! Get a system.
        template <typename SystemT>
        std::shared_ptr<SystemT> get_system();

        //! Get a system.
        template <typename SystemT>
        std::shared_ptr<const SystemT> get_system() const;

    protected:
        virtual void tick();

    private:
        std::string                  id;
        std::atomic<bool>            running;
        std::unique_ptr<Window>      window;
        std::unique_ptr<RenderQueue> render_queue;

        std::shared_ptr<Screen>      screen;
        std::shared_ptr<Scene>       scene, next_scene;
        std::shared_ptr<Camera>      camera, next_camera;

        std::chrono::steady_clock::time_point last_tick = std::chrono::steady_clock::now();

        std::vector<std::shared_ptr<System>> systems;

        void draw();
    };

    PKZO_EXPORT
    void show_error_dialog(const std::string_view caption, const std::string_view message);

    template <typename SystemT>
    void Engine::start_system()
    {
        assert(running == false);
        systems.push_back(std::make_shared<SystemT>(*this));
    }

    template <typename SystemT>
    std::shared_ptr<SystemT> Engine::get_system()
    {
        for (auto& system : systems)
        {
            auto system_t = std::dynamic_pointer_cast<SystemT>(system);
            if (system_t)
            {
                return system_t;
            }
        }
        throw nullptr;
    }

    //! Get a system.
    template <typename SystemT>
    std::shared_ptr<const SystemT> Engine::get_system() const
    {
        return const_cast<Engine*>(this)->get_system<SystemT>();
    }
}

#endif
