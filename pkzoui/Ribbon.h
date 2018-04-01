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

#ifndef _PKZO_RIBBON_H_
#define _PKZO_RIBBON_H_

#include <memory>
#include <string>
#include <functional>
#include <vector>

#include <pkzo2d/ScreenNodeGroup.h>
#include <pkzo2d/Rectangle.h>
#include <pkzo2d/Text.h>
#include <pkzo2d/HitArea.h>

namespace pkzo
{
    class Font;
    class Texture;

    class PKZO_EXPORT Ribbon : public ScreenNodeGroup
    {
    public:
        
        Ribbon();

        ~Ribbon();

        void set_width(int value);

        void set_font(std::shared_ptr<Font> value);

        std::shared_ptr<Font> get_font() const;

        void set_text_color(const rgm::vec4& value);

        const rgm::vec4& get_text_color();

        void set_background_color(const rgm::vec4& value);

        const rgm::vec4& get_background_color() const;

        void add_icon(std::shared_ptr<Texture> icon, const std::string& caption, std::function<void ()> cb);

    private:
        class Element : public ScreenNodeGroup
        {
        public:
            Element();

            void set_icon(std::shared_ptr<Texture> value);

            std::shared_ptr<Texture> get_icon() const;

            void set_caption(const std::string& value);

            const std::string& get_caption() const;

            void set_font(std::shared_ptr<Font> value);

            std::shared_ptr<Font> get_font() const;

            void set_text_color(const rgm::vec4& value);

            const rgm::vec4& get_text_color();

            void on_click(std::function<void ()> cb);

        private:
            Rectangle icon;
            Text      caption;
            HitArea   hitarea;

            void layout();
        };

        std::shared_ptr<Font> font;
       rgm::vec4                  text_color;
        
        Rectangle background;

        std::vector<std::unique_ptr<Element>> elements;
            
    };
}

#endif
