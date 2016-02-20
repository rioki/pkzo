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

#ifndef _PKZO_CAMERA_H_
#define _PKZO_CAMERA_H_

#include "Entity.h"

namespace pkzo
{
    class PKZO_EXPORT Camera : public Entity
    {
    public:
        
        Camera();

        ~Camera();

        void set_fov(float value);

        float get_fov() const;

        void set_distance(float value);

        float get_distance() const;

        mat4 get_projection_matrix(float aspect) const;

        mat4 get_view_matrix() const;

        void enqueue(SceneRenderer& queue, const Camera& camera) const override;
    
    private:
        float fov;
        float distance;
    };
}

#endif
