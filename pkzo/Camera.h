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

#include "SceneNode.h"

namespace pkzo
{
    //! Camera
    class PKZO_EXPORT Camera : public SceneNode
    {
    public:
        Camera() noexcept = default;
        Camera(const glm::mat4& transform) noexcept;


        void look_at(const glm::vec3 pos, const glm::vec3 target, const glm::vec3 up);

        void set_resolution(const glm::uvec2& value) noexcept;
        const glm::uvec2& get_resolution() const noexcept;

        float get_aspect() const noexcept;

        //! Set the FOV
        void set_fov(const float value) noexcept;
        //! Get the FOV
        float get_fov() const noexcept;

        //! Set the near clip plane
        void set_znear(const float value) noexcept;
        //! Get the near clip plane
        float get_znear() const noexcept;

        //! Set the far clip plane
        void set_zfar(const float value) noexcept;
        //! Get the far clip plane
        float get_zfar() const noexcept;

        glm::mat4 get_projection() const noexcept;
        glm::mat4 get_view() const noexcept;

    private:
        glm::uvec2 resolution = {800, 600};
        float      fov        = 45.0f;
        float      znear      = 0.01f;
        float      zfar       = 1000.0f;
    };
}
