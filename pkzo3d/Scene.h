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

#ifndef _PKZO_SCENE_H_
#define _PKZO_SCENE_H_

#include <list>

#include <pkzo/defines.h>

namespace pkzo
{
    class Entity;
    class Camera;
    class SceneRenderer;

    class PKZO_EXPORT Scene
    {
    public:

        Scene();

        Scene(const Scene&) = delete;

        virtual ~Scene();

        const Scene& operator = (const Scene&) = delete;

        void add_entity(Entity& entity);

        void remove_entity(Entity& entity);

        void draw(SceneRenderer& renderer, float aspect, const Camera& camera);

    private:
        std::list<Entity*> entities;
        
    };
}

#endif
