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

#ifndef _PKZO_ENTITY_H_
#define _PKZO_ENTITY_H_

#include <rgm/rgm.h>
#include <pkzo/defines.h>

namespace pkzo
{
    

    class Camera;
    class SceneRenderer;

    class PKZO_EXPORT Entity
    {
    public:
        
        Entity();

        Entity(const Entity&) = delete;

        virtual ~Entity();

        const Entity& operator = (const Entity&) = delete;

        void set_position(const rgm::vec3& value);

        const rgm::vec3& get_position() const;

        rgm::vec3 get_world_position() const;

        void set_orientation(const rgm::quat& value);

        const rgm::quat& get_orientation() const;

       rgm::quat get_world_orientation() const;

       rgm::mat4 get_transform() const;

       rgm::mat4 get_world_transform() const;

        virtual void enqueue(SceneRenderer& queue, const Camera& camera) const = 0;

    protected:
        Entity*   parent;
       rgm::vec3 position;
       rgm::quat orientation;
    };
}

#endif
