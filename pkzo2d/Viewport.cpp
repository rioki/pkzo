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

#include "Viewport.h"

#include <GL/glew.h>

namespace pkzo
{
    Viewport::Viewport() {}

    Viewport::~Viewport() {}

    void Viewport::on_draw(std::function<void ()> cb)
    {
        draw_cb = cb;
    }

    void Viewport::draw(Canvas& canvas, ivec2 offset) const
    {
        if (draw_cb)
        {
            int vp[4];
            glGetIntegerv(GL_VIEWPORT, vp);

            GLint x = position[0];
            GLint y = vp[3] - size[1] - position[1];
            GLsizei w = size[0];
            GLsizei h = size[1];

            glViewport(x, y, w, h);

            draw_cb();

            glViewport(vp[0], vp[1], vp[2], vp[3]);
        }
    }
}
