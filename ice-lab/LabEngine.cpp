// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "LabEngine.h"

#include "StaticBox.h"
#include "Pawn.h"

namespace lab
{
    std::filesystem::path get_config_folder()
    {
        PWSTR szPath = NULL;
        auto hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &szPath);
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to get %LOCALAPPDATA%.");
        }
        auto result = std::filesystem::path(szPath) / "ice/lab";
        CoTaskMemFree(szPath);
        return result;
    }

    std::filesystem::path get_project_dir()
    {
        return PROJECT_DIR;
    }

    std::filesystem::path get_asset_dir()
    {
        // TODO read this from environment (e.g. registry)
        return std::filesystem::path(SOLUTION_DIR) / "assets";
    }

    LabEngine::LabEngine()
    {
        auto config_dir = get_config_folder();
        // create config dir in all cases
        std::filesystem::create_directories(config_dir);

        if (std::filesystem::exists(config_dir / "settings.json"))
        {
            load_settings(config_dir / "settings.json");
        }
        else if(std::filesystem::exists(get_project_dir() / "settings.json"))
        {
            load_settings(get_project_dir() / "settings.json");
        }

        add_asset_folder(get_asset_dir());

        start_system<ice::SdlGraphicSystem>();
        start_system<ice::SdlInputSystem>();
        start_system<ice::ConsoleSystem>();

        auto* keyboard = get_keyboard();
        assert(keyboard);
        keyboard->on_key_up([this] (auto mod, auto key) {
            if (key == ice::Key::ESCAPE)
            {
                stop();
            }
        });

        auto* console = get_system<ice::ConsoleSystem>();
        console->define("exit", [this] (auto args) {
            stop();
        });
        console->define("echo", [this, console] (auto args) {
            auto line = ice::join({begin(args) + 1, end(args)}, " ");
            console->write(line);
        });

        set_scene(create_test_scene());
    }

    std::shared_ptr<ice::Scene> LabEngine::create_test_scene()
    {
        // later save and load scenes, but for now just create a test scene

        auto scene = std::make_shared<ice::Scene>();

        auto gray_material = ice::make_simple_material(glm::vec3(0.75f));

        // fake global illiumunation
        auto light0 = std::make_shared<ice::AmbientLight>(glm::vec3{0.106, 0.161, 0.2});
        scene->add_node(light0);

        auto l1t = glm::inverse(glm::lookAt(glm::vec3(0.0), {1.0, -0.5, -1.}, {0.0, 1.0, 0.0}));
        auto light1 = std::make_shared<ice::DirectionalLight>(l1t, glm::vec3(0.839, 0.718, 0.573));
        scene->add_node(light1);

        auto light2 = std::make_shared<ice::DirectionalLight>(glm::mat4(1.0f), glm::vec3(0.125, 0.165, 0.329));
        scene->add_node(light2);

        // ground
        auto ground = std::make_shared<StaticBox>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f)), glm::vec3(1000.0f, 1000.0f, 1.0f), gray_material);
        scene->add_node(ground);

        // a couple boxes as position reference
        auto box1 = std::make_shared<StaticBox>(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.5f)), glm::vec3(1.0f, 1.0f, 1.0f), gray_material);
        scene->add_node(box1);
        auto box2 = std::make_shared<StaticBox>(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 10.0f, 0.5f)), glm::vec3(1.0f, 1.0f, 1.0f), gray_material);
        scene->add_node(box2);
        auto box3 = std::make_shared<StaticBox>(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -10.0f, 0.5f)), glm::vec3(1.0f, 1.0f, 1.0f), gray_material);
        scene->add_node(box3);
        auto box4 = std::make_shared<StaticBox>(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -10.0f, 0.5f)), glm::vec3(1.0f, 1.0f, 1.0f), gray_material);
        scene->add_node(box4);

        // pawn
        // TODO hock an "add scene" event and add the pawn
        pawn = std::make_shared<Pawn>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.5f)));
        scene->add_node(pawn);

        return scene;
    }
}


