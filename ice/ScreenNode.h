// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <glm/glm.hpp>
#include <rsig/rsig.h>

namespace ice
{
    class Screen;

    class ICE_EXPORT ScreenNode
    {
    public:
        ScreenNode() noexcept = default;
        ScreenNode(const glm::mat3& transform) noexcept;
        virtual ~ScreenNode() = default;

        ScreenNode* get_parent() noexcept;
        const ScreenNode* get_parent() const noexcept;

        virtual Screen* get_screen() noexcept;
        const Screen* get_screen() const noexcept;

        template <typename T>
        T* find_ancestor() noexcept;
        template <typename T>
        const T* find_ancestor() const noexcept;

        void set_transform(const glm::mat3& value) noexcept;
        [[nodiscard]] const glm::mat3& get_transform() const noexcept;
        [[nodiscard]] glm::mat3 get_world_transform() const noexcept;

        rsig::connection on_move(const std::function<void ()>& cb) noexcept;
        [[nodiscard]] rsig::signal<>& get_move_signal() noexcept;

        virtual void activate();
        virtual void deactivate();

    private:
        ScreenNode*    parent    = nullptr;
        glm::mat3      transform = glm::mat3(1.0f);
        rsig::signal<> move_signal;

        ScreenNode(const ScreenNode&) = delete;
        ScreenNode& operator = (const ScreenNode&) = delete;

        friend class ScreenNodeGroup;
    };

    template <typename T>
    T* ScreenNode::find_ancestor() noexcept
    {
        auto p = dynamic_cast<T*>(parent);
        if (nullptr != p)
        {
            return p;
        }
        if (parent != nullptr)
        {
            return parent->find_ancestor<T>();
        }
        return nullptr;
    }

    template <typename T>
    const T* ScreenNode::find_ancestor() const noexcept
    {
        return const_cast<ScreenNode*>(this)->find_ancestor<T>();
    }
}
