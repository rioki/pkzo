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

#include <filesystem>

#include <glm/glm.hpp>

#include "defines.h"
#include "Image.h"

struct FT_FaceRec_;
typedef FT_FaceRec_* FT_Face;

namespace pkzo
{
    struct FontMetrics
    {
        int ascent;
        int descent;
        int height;
    };

    class PKZO_EXPORT Font
    {
    public:
        Font(const std::filesystem::path& path, unsigned int size);
        Font(const std::vector<std::byte>& memory, unsigned int size);
        ~Font();

        Font(Font&& other) noexcept;
        Font& operator = (Font&& other) noexcept;

        const std::filesystem::path& get_file() const noexcept;

        unsigned int get_size() const noexcept;

        glm::uvec2 estimate(const std::string& text) const noexcept;
        glm::uvec2 estimate(const std::wstring& text) const noexcept;
        glm::uvec2 estimate(const std::u8string& text) const noexcept;
        glm::uvec2 estimate(const std::u16string& text) const noexcept;
        glm::uvec2 estimate(const std::u32string& text) const noexcept;

        Image render(const std::string& text) const noexcept;
        Image render(const std::wstring& text) const noexcept;
        Image render(const std::u8string& text) const noexcept;
        Image render(const std::u16string& text) const noexcept;
        Image render(const std::u32string& text) const noexcept;

        FontMetrics get_metrics() const noexcept;

    private:
        std::filesystem::path file;
        unsigned int          size = 0;
        FT_Face               face = nullptr;

        std::tuple<glm::uvec2, glm::uvec2> estimate_impl(const std::u32string& text) const noexcept;

        Font(const Font&) = delete;
        Font& operator = (const Font&) = delete;
    };
}
