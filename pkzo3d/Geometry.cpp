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

#include "Geometry.h"

#include "SceneRenderer.h"

namespace pkzo
{
    Geometry::Geometry()
    {
    }


    Geometry::~Geometry()
    {
    }

    void Geometry::set_mesh(std::shared_ptr<Mesh> value)
    {
        mesh = value;
    }

    std::shared_ptr<Mesh> Geometry::get_mesh() const
    {
        return mesh;
    }

    void Geometry::set_material(std::shared_ptr<Material> value)
    {
        material = value;
    }

    std::shared_ptr<Material> Geometry::get_material() const
    {
        return material;
    }

    void Geometry::enqueue(SceneRenderer& queue, const Camera& camera) const
    {
        if (mesh && material)
        {
            vec3 s = get_world_position();
            quat o = get_world_orientation();

            mat4 t(1);
            t = translate(t, s);
            t = rotate(t, o);

            queue.queue_geometry(t, *mesh, *material);
        }
    }
}
