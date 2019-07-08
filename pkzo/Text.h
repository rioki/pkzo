// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include "ScreenNode.h"

#include <string>

namespace pkzo
{
    class Mesh;
    class Font;
    class Material;
    class Texture;

    class PKZO_EXPORT Text : public ScreenNode
    {
    public:
        explicit
        Text(const glm::vec2& position, const std::string& text, const std::shared_ptr<Font>& font, const std::shared_ptr<Material>& material);

        void set_text(const std::string& value);

        const std::string& get_text() const;

        void set_font(const std::shared_ptr<Font>& value);

        const std::shared_ptr<Font>& get_font();

        void set_material(const std::shared_ptr<Material>& value);

        const std::shared_ptr<Material>& get_material() const;

        void draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) override;

    private:
        std::shared_ptr<Mesh> mesh;
        std::string text;
        std::shared_ptr<Font> font;
        std::shared_ptr<Material> material;
        std::shared_ptr<Texture> texture;
    };
}

#endif
