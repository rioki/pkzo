/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef _PKZO_FONT_H_
#define _PKZO_FONT_H_

#include <memory>
#include <string>
#include <rgm/rgm.h>

#include "defines.h"
#include "Texture.h"
#include "TTFSentry.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace pkzo
{
    class PKZO_EXPORT Font
    {
    public:
        Font();

        Font(const std::string& file, unsigned int size);

        Font(const Font&) = delete;

        ~Font();

        const Font& operator = (const Font&) = delete;

        void load(const std::string& file, unsigned int size);

       rgm::ivec2 estimate(const std::string& text) const;

        Texture render(const std::string& text) const;

    private:
        TTFSentry ttf_sentry;

        TTF_Font* font; 
    };

    PKZO_EXPORT
    std::shared_ptr<Font> load_font(const std::string& file, unsigned int size);
}

#endif
