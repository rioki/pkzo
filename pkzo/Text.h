// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_TEXT_H_
#define _PKZO_TEXT_H_

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

        ~Text();

        void set_text(const std::string& value);

        const std::string& get_text() const;

        void set_font(const std::shared_ptr<Font>& value);

        const std::shared_ptr<Font>& get_font();

        void set_material(const std::shared_ptr<Material>& value);

        const std::shared_ptr<Material>& get_material() const;

        void enqueue(RenderQueue& queue) override;

    private:
        std::string text;
        std::shared_ptr<Font> font;
        std::shared_ptr<Material> material;
        std::shared_ptr<Material> material_instance;
    };
}

#endif
