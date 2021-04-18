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
#include <pkzo/Parameters.h>
#include <glm/glm.hpp>

namespace pkzo::three
{
    //! Material
    class PKZO_EXPORT Material
    {
    public:

        void set_base_color_factor(const glm::vec4& value) noexcept;
        const glm::vec4& get_base_color_factor() const noexcept;

        void set_base_color_map(const std::shared_ptr<Texture>& value) noexcept;
        const std::shared_ptr<Texture>& get_base_color_map() const noexcept;

        std::shared_ptr<Parameters> to_parameters() const noexcept;

    private:
        glm::vec4                base_color_factor = {1.0f, 1.0f, 1.0f, 1.0f};
        std::shared_ptr<Texture> base_color_map;
    };
}