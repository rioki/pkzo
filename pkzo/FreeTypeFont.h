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

#include "Font.h"

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

    class PKZO_EXPORT FreeTypeFont : public Font
    {
    public:
        static std::shared_ptr<Font> load(const std::filesystem::path& file);

        FreeTypeFont(const std::filesystem::path& file);
        ~FreeTypeFont();

        glm::uvec2 estimate(const std::u8string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;
        glm::uvec2 estimate(const std::u16string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;
        glm::uvec2 estimate(const std::u32string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;

        std::shared_ptr<Texture> render(const std::u8string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;
        std::shared_ptr<Texture> render(const std::u16string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;
        std::shared_ptr<Texture> render(const std::u32string_view text, unsigned int pt_size, unsigned int dpi = 72) const override;

        FontMetrics get_metrics(unsigned int pt_size, unsigned int dpi) const;

    private:
        FT_Face face;

        std::tuple<glm::uvec2, glm::uvec2> estimate_impl(const std::u32string_view text, unsigned int pt_size, unsigned int dpi) const;
    };
}
