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

#ifndef _PKZO_TEXT_H_
#define _PKZO_TEXT_H_

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "Widget.h"

namespace pkzo
{
    class Font;
    class Texture;

    class PKZO_EXPORT Text : public Widget
    {
    public:
        
        Text();

        ~Text();

        void set_font(std::shared_ptr<Font> value);

        std::shared_ptr<Font> get_font() const;

        void set_text(const std::string& value);

        const std::string& get_text() const;

        void set_color(const vec4& value);

        const vec4& get_color() const;

        void draw(Canvas& canvas) const override;

    private:
        std::shared_ptr<Font> font;
        std::string           text;
        vec4                  color;

        mutable bool                 dirty;
        mutable std::vector<Texture> textures;

        void estimate();
    };
}

#endif

