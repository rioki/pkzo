// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "OrbitSpectator.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mats
{
    OrbitSpectator::OrbitSpectator(pkzo::Engine& engine, const glm::vec3& p)
    : pivot(p)
    {
        update();

        auto mouse = engine.get_mouse();
        assert(mouse);
        mouse->on(pkzo::Mouse::BUTTON_PRESS, [this] (glm::uint button, glm::uvec2 pos) {
            if (button == 2)
            {
                panning = true;
            }
            if (button == 3)
            {
                orbiting = true;
            }
        });
        mouse->on(pkzo::Mouse::BUTTON_RELEASE, [this] (glm::uint button, glm::uvec2 pos) {
            if (button == 2)
            {
                panning = false;
            }
            if (button == 3)
            {
                orbiting = false;
            }
        });
        mouse->on(pkzo::Mouse::WHEEL, [this] (glm::ivec2 mov) {
            coords.z += 0.5f * static_cast<float>(mov.y);
            update();
        });
        mouse->on(pkzo::Mouse::MOVE, [this] (glm::ivec2 rel, glm::uvec2 pos) {
            if (orbiting)
            {
                coords.xy -= glm::vec2(rel) * glm::vec2{0.01f, 0.01f};
                update();
            }
            else if (panning)
            {
                coords.z -= 0.1f * static_cast<float>(rel.y);
                update();
            }
        });
    }

    void OrbitSpectator::set_pivot(const glm::vec3& value)
    {
        pivot = value;
    }

    const glm::vec3& OrbitSpectator::get_pivor() const
    {
        return pivot;
    }

    void OrbitSpectator::update()
    {
        auto transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(coords.x), {0.0f, 0.0f, 1.0f});
        transform = glm::rotate(transform, glm::radians(coords.y), {0.0f, 1.0f, 0.0f});
        transform = glm::translate(transform, {0.0f, 0.0f, coords.z});
        set_transform(transform);
    }
}
