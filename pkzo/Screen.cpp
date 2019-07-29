// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "pch.h"
#include "Screen.h"

#include "dbg.h"
#include "ScreenNode.h"
#include "RenderQueue.h"

namespace pkzo
{
    Screen::Screen(const glm::vec2& s)
    : size(s)
    {
        PKZO_ASSERT(glm::all(glm::lessThan(glm::vec2(0.0f), size)));
    }

    Screen::~Screen() = default;

    const glm::vec2& Screen::get_size() const
    {
        return size;
    }

    void Screen::set_size(const glm::vec2& value)
    {
        PKZO_ASSERT(glm::all(glm::lessThan(glm::vec2(0.0f), value)));
        size = value;
    }

    void Screen::add_node(const std::shared_ptr<ScreenNode>& node)
    {
        PKZO_ASSERT(node->screen == nullptr);
        nodes.push_back(node);
        node->screen = this;
    }

    void Screen::remove_node(const std::shared_ptr<ScreenNode>& node)
    {
        PKZO_ASSERT(node->screen == this);
        auto i = std::find(nodes.begin(), nodes.end(), node);
        if (i == nodes.end())
        {
            PKZO_THROW(std::invalid_argument, "Node is not in scene.``");
        }
        node->screen = nullptr;
        nodes.erase(i);
    }

    void Screen::draw(RenderQueue& queue)
    {
        queue.clear();

        auto hs = size / 2.0f;
        queue.set_othro_camera(-hs.x, hs.x, -hs.y, hs.y, -1.0f, 1.0f);

        for (auto& node : nodes)
        {
            node->enqueue(queue);
        }

        queue.execute(RenderAlgorithm::UNLIT);
    }
}