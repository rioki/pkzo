//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once
#include <pkzo/config.h>
#include <glm/glm.hpp>

namespace pkzo::three
{
    //! Scene Node
    class PKZO_EXPORT SceneNode
    {
    public:
        SceneNode() noexcept = default;
        SceneNode(const glm::mat4& transform) noexcept;
        SceneNode(const SceneNode&) = delete;
        virtual ~SceneNode() = default;
        SceneNode& operator = (const SceneNode&) = delete;

        //! Get the node's parent.
        //!
        //! @return the node's parent, can be nullptr
        //! @{
        SceneNode* get_parent() noexcept;
        const SceneNode* get_parent() const noexcept;
        //! @}

        //! Set the node's transform.
        void set_transform(const glm::mat4& value) noexcept;
        //! Get the node's transform.
        const glm::mat4& get_transform() const noexcept;
        //! Get the node's transform relative to the scene root.
        glm::mat4 get_world_transform() const noexcept;

    protected:
        //! Handle attaching to parent.
        virtual void on_attach(SceneNode* parent) noexcept;
        //! Handle detaching from parent.
        virtual void on_detach() noexcept;

    private:
        SceneNode* parent    = nullptr;
        glm::mat4  transform = glm::mat4(1.0f);

        friend class SceneNodeGroup;
    };
}