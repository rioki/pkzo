// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Scene.h"

#include "Renderer.h"
#include "Camera.h"

namespace pkzo
{
    Scene::Scene() = default;

    Scene::Scene(const std::filesystem::path& f)
    : file(f)
    {
        auto input = std::ifstream(file);
        auto jscene = nlohmann::json::parse(input);
        deserialize(jscene, f.parent_path());
    }

    Scene::Scene(const Scene& other)
    : Group(other) {}

    Scene::~Scene() = default;

    const std::filesystem::path& Scene::get_file() const noexcept
    {
        return file;
    }

    std::string Scene::get_type() const noexcept
    {
        return "Scene";
    }

    std::unique_ptr<SceneNode> Scene::clone() const noexcept
    {
        return std::make_unique<Scene>(*this);
    }

    bool Scene::is_active() const noexcept
    {
        return active;
    }

    void Scene::activate()
    {
        check(renderer == nullptr);

        active = true;
        renderer = std::make_unique<Renderer>();

        Group::activate();
    }

    void Scene::deactivate()
    {
        Group::deactivate();

        active = false;
        renderer = nullptr;
    }

    void Scene::save(const std::filesystem::path& path) const
    {
        auto jscene = nlohmann::json::object();
        serialize(jscene, path.parent_path());

        auto file = std::ofstream(path);
        file << jscene;
    }

    Renderer& Scene::get_renderer()
    {
        check(renderer != nullptr);
        return *renderer;
    }

    void Scene::draw(glm::uvec2 resolution) const
    {
        renderer->set_resolution(resolution);
        renderer->execute();
    }
}
