// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "config.h"

#include <tuple>
#include <memory>
#include <filesystem>
#include <glm/glm.hpp>

#include "Asset.h"

typedef struct FT_LibraryRec_  *FT_Library;
typedef struct FT_FaceRec_  *FT_Face;

namespace ice
{
    class Texture;

    class ICE_EXPORT Font : public Asset
    {
    public:
        Font(const std::filesystem::path& file, unsigned int size);
        ~Font();

        const std::filesystem::path& get_file() const noexcept;
        unsigned int get_size() const noexcept;

        glm::uvec2 estimate(const std::string& text) const noexcept;
        std::shared_ptr<Texture> render(const std::string& text) const noexcept;

    private:
        static FT_Library init_ft_library();

        FT_Library            ft_library = init_ft_library();
        FT_Face               face;
        std::filesystem::path file;
        unsigned int          size;

        std::tuple<glm::uvec2, glm::uvec2> estimate_impl(const std::u32string& text) const noexcept;

        Font(const Font&) = delete;
        Font& operator = (const Font&) = delete;
    };
}
