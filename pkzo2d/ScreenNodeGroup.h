//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _PKZO2D_SCREEN_NODE_GROUP_H_
#define _PKZO2D_SCREEN_NODE_GROUP_H_

#include "config.h"

#include <memory>
#include <list>
#include <glm/glm.hpp>

#include "ScreenNode.h"

namespace pkzo2d
{
    class PKZO2D_EXPORT ScreenNodeGroup : public ScreenNode
    {
    public:
        ScreenNodeGroup();
        ~ScreenNodeGroup();

        void set_position(const glm::vec2& value) noexcept;
        const glm::vec2& get_position() const noexcept;

        void add_node(const std::shared_ptr<ScreenNode>& node) noexcept;
        void remove_nodes(const std::shared_ptr<ScreenNode>& node) noexcept;

        const std::list<std::shared_ptr<ScreenNode>>& get_nodes() noexcept;
        std::list<std::shared_ptr<const ScreenNode>> get_nodes() const noexcept;

        void handle_mouse_button_down(MouseButton button, glm::vec2 position) override;
        void handle_mouse_button_up(MouseButton button, glm::vec2 position) override;

    protected:
        void render(ScreenRenderer& renderer, const glm::vec2& offset) const noexcept override;

    private:
        glm::vec2 position = glm::vec2(0.0f);
        std::list<std::shared_ptr<ScreenNode>> nodes;
    };
}

#endif
