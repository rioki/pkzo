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

        ~Rectangle();

        void set_material(const std::shared_ptr<Material>& value);

        const std::shared_ptr<Material>& get_material() const;

        void enqueue(RenderQueue& queue) override;

    private:
        std::shared_ptr<Material> material;
    };
}

#endif
