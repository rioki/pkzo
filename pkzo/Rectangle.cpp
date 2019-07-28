// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Rectangle.h"

#include <glm/gtc/matrix_transform.hpp>

#include "RenderQueue.h"
#include "Material.h"

namespace pkzo
{
    Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Material>& m)
    : ScreenNode(position, size),
      material(m) {}

    Rectangle::~Rectangle() = default;

    void Rectangle::set_material(const std::shared_ptr<Material>& value)
    {
        material = value;
    }

    const std::shared_ptr<Material>& Rectangle::get_material() const
    {
        return material;
    }

    void Rectangle::enqueue(RenderQueue& queue)
    {
        auto model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(get_position(), 0.0f));
        auto texture_matrix = glm::mat3(1.0f);
        texture_matrix[1][1] = -1.0;

        queue.submit_rectangle(model_matrix, get_size(), material, texture_matrix);
    }
}
