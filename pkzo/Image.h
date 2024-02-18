// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#include <memory>
#include <filesystem>

#include <glm/glm.hpp>
#include "defines.h"

struct FIBITMAP;

namespace pkzo
{
    enum class ColorMode
    {
        RGB,
        BGR,
        RGBA,
        BGRA
    };

    class PKZO_EXPORT Image
    {
    public:
        Image() noexcept = default;
        Image(const std::filesystem::path& path);
        Image(glm::uvec2 size, ColorMode mode, const uint8_t* memory = nullptr);
        ~Image();

        Image(Image&& other) noexcept;
        Image& operator = (Image&& other) noexcept;

        const std::filesystem::path& get_file() const noexcept;

        glm::uvec2 get_size() const noexcept;
        ColorMode get_color_mode() const noexcept;
        const uint8_t* get_data() const noexcept;

        glm::vec4 get_pixel(glm::uvec2 pos) const noexcept;
        void set_pixel(glm::uvec2 pos, glm::vec4 color) noexcept;

        void save(const std::filesystem::path& file) const;

    private:
        std::filesystem::path file;
        FIBITMAP* bitmap = nullptr;

        Image(const Image&) = delete;
        Image& operator = (const Image&) = delete;
    };

    PKZO_EXPORT float compare(const Image& a, const Image& b);
    PKZO_EXPORT Image diff(const Image& a, const Image& b);
}

template<>
struct std::hash<pkzo::Image>
{
    std::size_t operator()(const pkzo::Image& image) const noexcept
    {
        return reinterpret_cast<size_t>(image.get_data());
    }
};
