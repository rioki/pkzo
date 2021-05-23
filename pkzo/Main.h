//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "config.h"

#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <mutex>
#include <string>
#include <filesystem>
#include <glm/fwd.hpp>

#include "rsig.h"
#include "enums.h"
#include "SdlSentry.h"

namespace pkzo
{
    class Mouse;
    class Keyboard;
    class Joystick;
    class Window;
    class Settings;
    class Scene;
    class Camera;

    constexpr EngineInit DEFAULT_ENGINE_INIT = EngineInit::LOAD_SETTINGS
                                             | EngineInit::WINDOW
                                             | EngineInit::HANDLE_DRAW
                                             | EngineInit::ROUTE_EVENTS;

    //! Main object, controller of all
    class PKZO_EXPORT Main
    {
    public:
        //! Construct Engine
        //!
        //! @param id the engine id.
        explicit Main(const std::string& id, EngineInit init = DEFAULT_ENGINE_INIT);
        Main(const Main&) = delete;
        ~Main();
        Main& operator = (const Main&) = delete;

        //! Get the engine's id.
        const std::string& get_id() const noexcept;

        //! Get the folder that can be used to store user specific persistent data.
        std::filesystem::path get_user_folder() const;
        //! Get the folder that can be used to store throw away data.
        std::filesystem::path get_temp_folder() const;

        Settings& get_settings() noexcept;
        const Settings& get_settings() const noexcept;

        Mouse& get_mouse() noexcept;
        const Mouse& get_mouse() const noexcept;

        Keyboard& get_keyboard() noexcept;
        const Keyboard& get_keyboard() const noexcept;

        size_t get_joystick_count() const noexcept;
        Joystick& get_joystick(size_t id) noexcept;
        const Joystick& get_joystick(size_t id) const noexcept;

        Window& open_window(const glm::uvec2& size, WindowMode mode = WindowMode::STATIC, const std::string_view caption = "pkzo");

        Window& get_main_window() noexcept;
        const Window& get_main_window() const noexcept;

        //! Get the number of windows open.
        size_t get_open_windows() const noexcept;

        //! Get the window with the given index.
        //!
        //! @{
        Window& get_window(size_t index) noexcept;
        const Window& get_window(size_t index) const noexcept;
        //! @}

        //! Change the current scene.
        //!
        //! @note The scene will only become active at the next frame.
        void change_scene(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Camera>& camera) noexcept;

        //! Change the primary camera.
        void change_camera(const std::shared_ptr<Camera>& camera) noexcept;

        //! Get the current active scene.
        //!
        //! @{
        const std::shared_ptr<Scene>& get_scene() noexcept;
        std::shared_ptr<const Scene> get_scene() const noexcept;
        //! @}

        //! Get the current active primart camera.
        //!
        //! @{
        const std::shared_ptr<Camera>& get_camera() noexcept;
        std::shared_ptr<const Camera> get_camera() const noexcept;
        //! @}

        int run();
        void tick();
        void stop();

        //! Singal emitted every frame.
        //! @{
        rsig::signal<std::chrono::milliseconds>& get_tick_signal() noexcept;
        rsig::connection on_tick(const std::function<void (std::chrono::milliseconds)>& cb);
        //! @}

        //! Signal emitted when stop is requeted.
        //! @{
        rsig::signal<>& get_quit_signal() noexcept;
        rsig::connection on_quit(const std::function<void ()>& cb);
        //! @}

    private:
        SdlSentry sdl_sentry;
        mutable std::recursive_mutex mutex;
        std::string id;
        mutable std::filesystem::path user_folder;
        mutable std::filesystem::path temp_folder;
        bool running = false;
        std::chrono::steady_clock::time_point  last_tick;

        std::unique_ptr<Settings>              settings;
        std::unique_ptr<Mouse>                 mouse;
        std::unique_ptr<Keyboard>              keyboard;
        std::vector<std::unique_ptr<Joystick>> joysticks;
        std::vector<std::unique_ptr<Window>>   windows;

        std::shared_ptr<Scene> scene;
        std::shared_ptr<Scene> next_scene;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Camera> next_camera;

        rsig::signal<std::chrono::milliseconds> tick_signal;
        rsig::signal<>                          quit_signal;

        void handle_events();
        void switch_scenes();
    };
}
