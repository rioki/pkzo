#pragma once
class MemoryTexture
{
};


// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "Texture.h"

namespace pkzo
{
    class PKZO_EXPORT MemoryTexture : public Texture
    {
    public:

        static std::shared_ptr<MemoryTexture> create(const CreateSpecs& specs);

        virtual glm::vec4 get_pixel(const glm::uvec2& pos) const = 0;
        virtual void set_pixel(const glm::uvec2& pos, const glm::vec4& value) = 0;

        virtual void save(const std::filesystem::path& file) const = 0;
    };

    PKZO_EXPORT float compare(const std::shared_ptr<MemoryTexture>& a, const std::shared_ptr<MemoryTexture>& b);
    PKZO_EXPORT std::shared_ptr<MemoryTexture> diff(const std::shared_ptr<MemoryTexture>& a, const std::shared_ptr<MemoryTexture>& b);
}
