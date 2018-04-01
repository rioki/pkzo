// 
// pkzo
// 
// Copyright 2014-2018 Sean Farrell <sean.farrell@rioki.org>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _PKZO_SCREEN_H_
#define _PKZO_SCREEN_H_

#include <memory>
#include <tuple>
#include <list>

#include <rgm/rgm.h>
#include <pkzo/defines.h>

namespace pkzo
{
    class ScreenNode;
    class Canvas;
    class Texture;

    class PKZO_EXPORT Screen
    {
    public:
        Screen(const rgm::ivec2& size);

        Screen(const Screen&) = delete;

        virtual ~Screen();

        const Screen& operator = (const Screen&) = delete;

        void set_size(const rgm::ivec2& value);

        const rgm::ivec2& get_size() const;

        void set_background_color(const rgm::vec4& value);

        const rgm::vec4& get_background_color() const;

        void set_background_texture(std::shared_ptr<Texture> value);

        std::shared_ptr<Texture> get_background_texture() const;

        void add_node(ScreenNode& node);

        void remove_node(ScreenNode& node);

        virtual void draw(Canvas& canvas) const;

        virtual void handle_mouse_move(rgm::ivec2 pos, rgm::ivec2 mov);

        virtual void handle_mouse_press(unsigned int button, rgm::ivec2 pos);

        virtual void handle_mouse_release(unsigned int button, rgm::ivec2 pos);

    private:
       rgm::ivec2 size;

        std::list<ScreenNode*> nodes;

        rgm::vec4                background_color;
        std::shared_ptr<Texture> background_texture;
    };
}

#endif
