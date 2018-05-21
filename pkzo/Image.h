/*
  pkzo

  Copyright (c) 2014-2017 Sean Farrell

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

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <memory>
#include <string>
#include <vector>

#include <rgm/rgm.h>

#include "defines.h"
#include "SDLSentry.h"

struct SDL_Surface;

namespace glow
{
    class Texture;
}

namespace pkzo
{
    enum ColorType
    {
        NOCOLOR,
        MONOCHROME,
        RGB,
        RGBA
    };

    class PKZO_EXPORT Image
    {
    public:

        Image(const std::string& file);

        Image(const std::string& file_xpos, const std::string& file_xneg, 
              const std::string& file_ypos, const std::string& file_yneg,
              const std::string& file_zpos, const std::string& file_zneg);

        Image(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data);

        Image(SDL_Surface* surface);
        
        Image(const Image&) = delete;

        ~Image();

        const Image& operator = (const Image&) = delete;

        rgm::uvec2 get_size() const;

        ColorType get_color_type() const;

        const unsigned char* get_data() const;

    private:
        SDLSentry sdl_sentry;

        std::vector<SDL_Surface*>      surfaces;
    };
}

#endif
