//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "Actor.h"

#include "Scene.h"

namespace pkzo
{
    Actor::Actor(const glm::mat4& transform) noexcept
    : SceneNodeGroup(transform) {}

    void Actor::on_attach_scene(Scene* scene) noexcept
    {
        DBG_ASSERT(scene);
        SceneNodeGroup::on_attach_scene(scene);
        scene->register_actor(this);
    }

    void Actor::on_detach_scene() noexcept
    {
        auto scene = get_scene();
        DBG_ASSERT(scene);
        scene->unregister_actor(this);
        SceneNodeGroup::on_detach_scene();
    }

    void Actor::update(std::chrono::milliseconds dt) noexcept
    {

        SceneNodeGroup::update(dt);
    }

    void Actor::handle_key_press(Key key, KeyMod mod) noexcept {}

    void Actor::handle_key_release(Key key, KeyMod mod) noexcept {}

    void Actor::handle_mouse_move(glm::vec2 pos, glm::vec2 rel) noexcept {}

    void Actor::handle_mouse_press(MouseButton button, glm::vec2 pos) noexcept {}

    void Actor::handle_mouse_release(MouseButton button, glm::vec2 pos) noexcept {}
}
