// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Text.h"

#include <glm/gtc/matrix_transform.hpp>

#include "dbg.h"
#include "RenderQueue.h"
#include "Font.h"
#include "Texture.h"
#include "Material.h"

namespace pkzo
{
    glm::vec2 safe_estimate(const std::shared_ptr<Font>& font, const std::string& text)
    {
        if (font)
        {
            return font->estimate(text);
        }
        else
        {
            return glm::vec2(15, 15);
        }
    }

    Text::Text(const glm::vec2& position, const std::string& t, const std::shared_ptr<Font>& f,  const std::shared_ptr<Material>& m)
    : ScreenNode(position, safe_estimate(f, t)),
      text(t),
      font(f),
      material(m) {}

    Text::~Text() = default;

    void Text::set_text(const std::string& value)
    {
        text = value;
        material_instance = nullptr;
    }

    const std::string& Text::get_text() const
    {
        return text;
    }

    void Text::set_font(const std::shared_ptr<Font>& value)
    {
        font = value;
        material_instance = nullptr;
    }

    const std::shared_ptr<Font>& Text::get_font()
    {
        return font;
    }

    void Text::set_material(const std::shared_ptr<Material>& value)
    {
        material = value;
    }

    const std::shared_ptr<Material>& Text::get_material() const
    {
        return material;
    }

    void Text::enqueue(RenderQueue& queue) const
    {
        PKZO_ASSERT(font);
        PKZO_ASSERT(material);

        if (!material_instance)
        {
            material_instance = std::make_shared<Material>(*material);
            material_instance->set_texture("pkzo_Mask", font->render(text));
        }

        auto model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(get_position(), 0.0f));
        auto texture_matrix = glm::mat3(1.0f);
        texture_matrix[1][1] = -1.0;

        queue.submit_rectangle(model_matrix, get_size(), material_instance, texture_matrix);
    }
}
