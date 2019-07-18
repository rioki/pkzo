// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Text.h"

#include "Shader.h"
#include "Mesh.h"
#include "Font.h"
#include "Material.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>

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
      mesh(Mesh::create_rectangle(glm::vec2(1.0), true)),
      text(t),
      font(f),
      material(m) {}

    Text::~Text() = default;

    void Text::set_text(const std::string& value)
    {
        text = value;
        texture = nullptr;
    }

    const std::string& Text::get_text() const
    {
        return text;
    }

    void Text::set_font(const std::shared_ptr<Font>& value)
    {
        font = value;
        texture = nullptr;
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

    void Text::draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model)
    {
        if (!mesh || !material || !font)
        {
            return;
        }
        auto shader = material->get_shader();
        if (!shader)
        {
            return;
        }

        if (!texture)
        {
            texture = font->render(text);
        }

        auto local_model = glm::translate(model, glm::vec3(get_position(), 0.0f));
        local_model = glm::scale(local_model, glm::vec3(get_size(), 1.0f));

        shader->bind();
        shader->set_uniform("pkzo_ProjectionMatrix", proj);
        shader->set_uniform("pkzo_ViewMatrix", view);
        shader->set_uniform("pkzo_ModelMatrix", local_model);
        shader->set_texture("pkzo_Text", texture);
        material->bind(*shader);
        mesh->bind(*shader);
        mesh->draw();
        mesh->unbind();
        material->unbind();
        shader->unbind();
    }
}
