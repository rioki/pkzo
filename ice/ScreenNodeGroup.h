// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include "ScreenNode.h"

#include <memory>
#include <vector>

namespace ice
{
    class ICE_EXPORT ScreenNodeGroup : public ScreenNode
    {
    public:
        ScreenNodeGroup() noexcept = default;
        ScreenNodeGroup(const glm::mat3& transform) noexcept;

        void add_node(ScreenNode& node) noexcept;
        void add_node(const std::shared_ptr<ScreenNode>& node) noexcept;

        void remove_node(ScreenNode& node) noexcept;
        void remove_node(const std::shared_ptr<ScreenNode>& node) noexcept;

        std::vector<ScreenNode*> get_nodes() noexcept;
        std::vector<const ScreenNode*> get_nodes() const noexcept;


        void activate() override;
        void deactivate() override;

    private:
        std::vector<std::shared_ptr<ScreenNode>> nodes;
    };
}
