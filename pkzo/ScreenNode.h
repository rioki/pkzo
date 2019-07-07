// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SCREEN_NODE_H_
#define _PKZO_SCREEN_NODE_H_

#include <glm/glm.hpp>

#include "defines.h"
#include "stdex.h"

namespace pkzo
{
    class Screen;

    class PKZO_EXPORT ScreenNode : private stdex::non_copyable
    {
    public:
        explicit ScreenNode(const glm::vec2& position, const glm::vec2& size);

        virtual ~ScreenNode();

        void set_position(const glm::vec2& value);
        const glm::vec2& get_position() const;

        void set_size(const glm::vec2& value);
        const glm::vec2& get_size() const;

        virtual void draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);

    private:
        Screen* screen = nullptr;
        glm::vec2 position;
        glm::vec2 size;

    friend class Screen;
    };
}

#endif
