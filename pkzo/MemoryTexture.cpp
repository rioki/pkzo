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

#include "pch.h"

#include "MemoryTexture.h"

#include <tinyformat.h>

#include "FreeImageTexture.h"

namespace pkzo
{
    std::shared_ptr<MemoryTexture> MemoryTexture::create(const CreateSpecs& specs)
    {
        return std::make_shared<FreeImageTexture>(specs);
    }

    float compare(const std::shared_ptr<MemoryTexture>& a, const std::shared_ptr<MemoryTexture>& b)
    {
        if (a == b)
        {
            return 0.0f;
        }

        if (a == nullptr || b == nullptr)
        {
            throw std::runtime_error("compare: textures are null");
        }

        if (a->get_size() != b->get_size())
        {
            throw std::runtime_error("compare: textures are not the same size");
        }

        float error = 0.0f;

        auto s = a->get_size();
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a->get_pixel({u, v});
                auto bc = b->get_pixel({u, v});
                error += glm::length(glm::abs(ac - bc));
            }
        }

        return error;
    }

    void set_pixel(std::vector<uint8_t>& buffer, const glm::uvec2& size, const glm::uvec2& pos, const glm::vec4& color)
    {
        auto index = (pos.y * size.x + pos.x) * 4;
        buffer[index + 0] = static_cast<uint8_t>(color[0] * 255.0f);
        buffer[index + 1] = static_cast<uint8_t>(color[1] * 255.0f);
        buffer[index + 2] = static_cast<uint8_t>(color[2] * 255.0f);
        buffer[index + 3] = static_cast<uint8_t>(color[3] * 255.0f);
    }

    std::shared_ptr<MemoryTexture> diff(const std::shared_ptr<MemoryTexture>& a, const std::shared_ptr<MemoryTexture>& b)
    {
        if (a == nullptr || b == nullptr)
        {
            throw std::runtime_error("diff: textures are null");
        }

        if (a->get_size() != b->get_size())
        {
            throw std::runtime_error("diff: textures are not the same size");
        }

        auto size = a->get_size();
        auto buffer = std::vector<uint8_t>(size.x * size.y * 4u, 0u);
        for (auto u = 0u; u < size.x; u++)
        {
            for (auto v = 0u; v < size.y; v++)
            {
                auto ac = a->get_pixel({u, v});
                auto bc = b->get_pixel({u, v});
                auto diff = glm::abs(ac - bc);
                diff.a = 1.0f - diff.a;
                set_pixel(buffer, size, {u, v}, diff);
            }
        }

        return MemoryTexture::create({
            .id         = tfm::format("diff of %s and %s", a->get_id(), b->get_id()),
            .size       = size,
            .data_type  = DataType::UNSIGNED_BYTE,
            .color_mode = ColorMode::RGBA,
            .memory     = buffer.data()
        });
    }
}
