// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once
#include <pkzo/config.h>

#include <glm/glm.hpp>

namespace pkzo::three
{
    class Scene;

    //! The SceneNode class represents a basic node in a scene graph.
    class PKZO_EXPORT SceneNode
    {
    public:
        //! Default constructor initializes the node with identity transform and no parent.
        SceneNode() noexcept;

        //! Constructs a node with an initial transform.
        //!
        //! @param init_transform Initial transformation matrix for the node.
        SceneNode(const glm::mat4& init_transform) noexcept;

        virtual ~SceneNode() = default;

        //! Gets the transformation matrix of the node.
        //!
        //! @return Transformation matrix of the node.
        [[nodiscard]] glm::mat4 get_transform() const noexcept;

        //! Gets the global transformation matrix of the node.
        //!
        //! @return Global transformation matrix of the node.
        [[nodiscard]] glm::mat4 get_global_transform() const noexcept;

        //! Sets the transformation matrix of the node.
        //!
        //! @param new_transform New transformation matrix for the node.
        void set_transform(const glm::mat4& new_transform) noexcept;

        //! Gets the parent node of this node.
        //!
        //! @return Pointer to the parent node. Returns nullptr if no parent.
        [[nodiscard]] SceneNode* get_parent() const noexcept;

        //! Sets the parent node of this node.
        //!
        //! @param new_parent New parent node for this node.
        void set_parent(SceneNode* new_parent) noexcept;

        //! Retrieve the parent Scene of this SceneNode.
        //!
        //! @return Pointer to the parent Scene object or nullptr.
        Scene* get_scene() noexcept;

        //! Retrieve the parent Scene of this const SceneNode.
        //!
        //! @return Pointer to the const parent Scene object or nullptr.
        const Scene* get_scene() const noexcept;

    private:
        glm::mat4  transform = glm::mat4{1.0f};
        SceneNode* parent    = nullptr;

        SceneNode(const SceneNode&) = delete;
        SceneNode(SceneNode&&) = delete;
        SceneNode& operator = (const SceneNode&) = delete;
        SceneNode& operator = (SceneNode&&) = delete;
    };
}


