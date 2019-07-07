// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_RECTANGLE_H_
#define _PKZO_RECTANGLE_H_

#include "ScreenNode.h"

namespace pkzo
{
    class Mesh;
    class Material;

    class PKZO_EXPORT Rectangle : public ScreenNode
    {
    public:
        explicit
        Rectangle(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Material>& material);

        void set_material(const std::shared_ptr<Material>& value);

        const std::shared_ptr<Material>& get_material() const;

        void draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) override;

    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
    };
}

#endif
