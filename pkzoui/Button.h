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

#ifndef _PKZOUI_BUTTON_H_
#define _PKZOUI_BUTTON_H_

#include <pkzo2d/WidgetGroup.h>
#include <pkzo2d/Text.h>
#include <pkzo2d/Rectangle.h>
#include <pkzo2d/HitArea.h>

namespace pkzo
{
    class PKZO_EXPORT Button : public WidgetGroup
    {
    public:
        Button();

        ~Button();

        void set_label(const std::string& value);

        const std::string& get_label() const;

        void set_label_color(const rgm::vec4& value);

        const rgm::vec4& get_label_color() const;

        void set_label_font(std::shared_ptr<Font> value);

        std::shared_ptr<Font> get_label_font() const;

        void set_background_color(const rgm::vec4& value);

        const rgm::vec4& get_background_color() const;

        void set_background_texture(std::shared_ptr<Texture> value);

        std::shared_ptr<Texture> get_background_texture() const;

        void on_click(std::function<void ()> cb);

        void draw(Canvas& canvas, rgm::ivec2 offset) const override;

    private:
        Text      label;
        Rectangle background;
        HitArea   hitarea;
    };    
}

#endif
