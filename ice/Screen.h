// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include "ScreenNodeGroup.h"

namespace ice
{
    class ICE_EXPORT Screen : public ScreenNodeGroup
    {
    public:
        Screen(const glm::vec2& size);
        ~Screen();

        [[nodiscard]]
        const glm::vec2& get_size() const noexcept;
        void resize(const glm::vec2& value) noexcept;

        void activate() override;
        void deactivate() override;

        [[nodiscard]]
        bool is_active() const noexcept;

    private:
        glm::vec2 size;
        bool active = false;
    };

    ICE_EXPORT [[nodiscard]]
    glm::vec2 map_to_screen(glm::vec2 win_size, glm::vec2 screen_size, glm::vec2 pos);
}
