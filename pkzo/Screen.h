// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_SCREEN_H_
#define _PKZO_SCREEN_H_

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "defines.h"
#include "stdex.h"
#include "EventEmitter.h"

namespace pkzo
{
    class ScreenNode;

    /*!
     * 2D Stuff
     */
    class PKZO_EXPORT Screen : private stdex::non_copyable
    {
    public:
        /*!
         * Create a screen.
         *
         * @param size the initial size of the screen
         */
        explicit
        Screen(const glm::vec2& size);

        /*!
         * Get the screen size
         *
         * @return the screen size
         */
        const glm::vec2& get_size() const;

        /*!
         * Set the screen size
         *
         * @param value
         */
        void set_size(const glm::vec2& value);

        /*!
         * Add a node to the screen.
         *
         * @param node the node to add
         */
        void add_node(const std::shared_ptr<ScreenNode>& node);

        /*!
         * Remove a node from the screen.
         *
         * @param node the node to remove
         */
        void remove_node(const std::shared_ptr<ScreenNode>& node);

        /*!
         * Draw the screen.
         */
        void draw();

    private:
        glm::vec2 size;
        std::list<std::shared_ptr<ScreenNode>> nodes;
    };
}

#endif
