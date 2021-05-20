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

#include "config.h"
#include "Camera.h"

namespace pkzo
{
    //! Orthographic Camera
    //!
    //! This camera implements the orthographic projection. Ths means all lines
    //! that are paralell, remain paralell.
    class PKZO_EXPORT OrthographicCamera : public Camera
    {
    public:
        //! Construct Orthographic Camera
        OrthographicCamera() noexcept = default;

        //! Contruct Camera for a 2D screen.
        OrthographicCamera(const glm::vec2& size) noexcept;

        //! Get the volume of displayed space.
        const glm::vec3& get_size() const noexcept;
        //! Set the volume of displayed space.
        void set_size(const glm::vec3& value);

        glm::mat4 get_projection() const noexcept override;

    private:
        glm::vec3 size;
    };
}
