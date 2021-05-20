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

#pragma once

#include "config.h"

#include <memory>
#include <list>
#include <glm/glm.hpp>

#include "SceneNode.h"

namespace pkzo
{
    class Pipeline;
    class Material;

    //! Recangle in the X/Y plane.
    class PKZO_EXPORT Rectangle : public SceneNode
    {
    public:
        //! Construct a rectangle.
        //!
        //! @param transform the initial transformation
        //! @param size the size of the rectangle
        //! @param material
        //!
        //! @{
        Rectangle() noexcept;
        Rectangle(const glm::vec2& size, const std::shared_ptr<Material>& material) noexcept;
        Rectangle(const glm::mat4& transform, const glm::vec2& size, const std::shared_ptr<Material>& material) noexcept;
        //! @}

        ~Rectangle();

        //! Get the size of the rectangle.
        void set_size(const glm::vec2& value) noexcept;
        //! Set the size of the rectangle.
        const glm::vec2& get_size() const noexcept;

        //! Set the material of the rectangle.
        void set_material(const std::shared_ptr<Material>& value);
        //! Get the material of the rectangle.
        const std::shared_ptr<Material>& get_material() const;

    protected:
        void on_attach_scene(Scene* scene) noexcept override;
        void on_detach_scene() noexcept override;
        void update(std::chrono::milliseconds dt) noexcept override;

    private:
        glm::vec2                 size     = glm::vec2(15.0f);
        std::shared_ptr<Material> material = std::make_shared<Material>();

        Pipeline*             pipeline        = nullptr;
        unsigned int          pipeline_handle = 0;
        bool                  dirty = false;
    };
}
