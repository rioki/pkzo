// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "FlyPawn.h"

#include <glm/gtc/matrix_transform.hpp>

#include <pkzo/pkzo.h>
#include <pkzo/dbg.h>

namespace cubes
{
    FlyPawn::FlyPawn(pkzo::Engine& engine)
    {
        camera = std::make_shared<pkzo::Camera>();
        auto transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(-90.0f), {0.0f, 0.0f, 1.0f});
        transform = glm::rotate(transform, glm::radians(90.0f), {1.0f, 0.0f, 0.0f});
        camera->set_transform(transform);
        add_node(camera);

        auto& mouse = engine.get_mouse();
        mouse.on(pkzo::Mouse::BUTTON_PRESS, [this] (glm::uint button, glm::uvec2 pos) {
            if (button == 3)
            {
                rotating = true;
            }
        });
        mouse.on(pkzo::Mouse::BUTTON_RELEASE, [this] (glm::uint button, glm::uvec2 pos) {

            if (button == 3)
            {
                rotating = false;
            }
        });
        mouse.on(pkzo::Mouse::MOVE, [this] (glm::ivec2 rel, glm::uvec2 pos) {
            if (rotating)
            {
                rotation += glm::vec2(rel) * 0.1f;
            }
        });

        auto& keyboard = engine.get_keyboard();
        keyboard.on(pkzo::Keyboard::KEY_PRESS, [this] (pkzo::Key key) {
            switch (key)
            {
                case pkzo::KEY_W:
                    move_fore = true;
                    break;
                case pkzo::KEY_S:
                    move_back = true;
                    break;
                case pkzo::KEY_A:
                    move_left = true;
                    break;
                case pkzo::KEY_D:
                    move_right = true;
                    break;
                case pkzo::KEY_SPACE:
                    move_up = true;
                    break;
                case pkzo::KEY_LCTRL:
                    move_down = true;
                    break;
            }
        });
        keyboard.on(pkzo::Keyboard::KEY_RELEASE, [this] (pkzo::Key key) {
            switch (key)
            {
                case pkzo::KEY_W:
                    move_fore = false;
                    break;
                case pkzo::KEY_S:
                    move_back = false;
                    break;
                case pkzo::KEY_A:
                    move_left = false;
                    break;
                case pkzo::KEY_D:
                    move_right = false;
                    break;
                case pkzo::KEY_SPACE:
                    move_up = false;
                    break;
                case pkzo::KEY_LCTRL:
                    move_down = false;
                    break;
            }
        });
    }

    std::shared_ptr<pkzo::Camera> FlyPawn::get_camera() const
    {
        PKZO_ASSERT(camera);
        return camera;
    }

    void FlyPawn::update(float dt)
    {
        auto transform = get_transform();

        auto new_transform = glm::mat4(1.0f);
        new_transform = glm::translate(new_transform, glm::vec3(transform[3]) + get_target_velocity() * dt);
        new_transform = glm::rotate(new_transform, glm::radians(-rotation.x), glm::vec3{0.0f, 0.0f, 1.0f});
        new_transform = glm::rotate(new_transform, glm::radians(rotation.y), glm::vec3{0.0f, 1.0f, 0.0f}); // TODO setting invert mouse
        set_transform(new_transform);

        SceneNodeGroup::update(dt);
    }

    glm::vec3 FlyPawn::get_target_velocity() const
    {
        auto result = glm::vec3(0.0f);

        if (move_fore)
        {
            result.x += speed;
        }
        if (move_back)
        {
            result.x -= speed;
        }
        if (move_left)
        {
            result.y += speed;
        }
        if (move_right)
        {
            result.y -= speed;
        }

        result = glm::mat3(get_transform()) * result;

        if (move_up)
        {
            result.z += speed;
        }
        if (move_down)
        {
            result.z -= speed;
        }

        return result;
    }
}
