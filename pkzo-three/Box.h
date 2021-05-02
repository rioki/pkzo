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

#include "Geometry.h"

namespace pkzo::three
{
    //! Box
    class PKZO_EXPORT Box : public Geometry
    {
    public:
        //! Default Constructor
        Box() noexcept;

        //! Initializing Contructor
        //!
        //! @param transform
        //! @param size
        Box(const glm::mat4& transform, const glm::vec3& size) noexcept;

        Box(const glm::mat4& transform, const glm::vec3& size, const std::shared_ptr<Material>& material) noexcept;

        //! Get the box's size.
        const glm::vec3& get_size() const noexcept;

        std::shared_ptr<Mesh> get_mesh() const noexcept override;

    private:
        glm::vec3 size = {1.0f, 1.0f, 1.0f};
        std::shared_ptr<Mesh> mesh;
    };
}
