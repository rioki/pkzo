//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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

#ifndef _ICE_FONT_H_
#define _ICE_FONT_H_

#include "config.h"

#include <memory>
#include <filesystem>
#include <glm/fwd.hpp>

#include "SdlSentry.h"

typedef struct _TTF_Font TTF_Font;

namespace pkzo
{
    class Texture;

    //! True Type Font
    class PKZO_EXPORT Font
    {
    public:
        //! Load font from file.
        //!
        //! @param file the font file to load
        //! @param size the font size to load
        //! @returns the requested font
        //! @excaption file_not_found
        static std::shared_ptr<Font> load(const std::filesystem::path& file, unsigned int size);

        Font(const std::filesystem::path& file, unsigned int size);
        Font(const Font&) = delete;
        ~Font();
        Font& operator = (const Font&) = delete;

        //! Get the font file.
        const std::filesystem::path& get_file() const noexcept;

        //! Get the font size.
        unsigned int get_size() const noexcept;

        //! Estimate the size of a text.
        //!
        //! @param text the text to render
        //! @return the size the resulting texture will be when rendered.
        glm::uvec2 estimate(const std::string& text) const noexcept;

        //! Render font to texture.
        //!
        //! @param text the text to render
        //! @return a texture with the text rendered as black and white mask.
        std::shared_ptr<Texture> render(const std::string& text) const noexcept;

    private:
        SdlSentry             sdl_sentry;
        std::filesystem::path file;
        unsigned int          size;
        TTF_Font*             font = nullptr;
    };
}

#endif
