// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "Scene.h"

#include <pkzo/Mesh.h>

namespace pkzo
{
    using pkzo::Mesh;
    class Material;

    class PKZO_EXPORT Geometry : public SceneNode
    {
    public:
        struct Init
        {
            SceneNode*                parent     = nullptr;
            glm::mat4                 transform  = glm::mat4(1.0f);
            bool                      visible    = true;
            bool                      collidable = true;
            std::shared_ptr<Material> material;
        };

        Geometry(Init init);

        ~Geometry();

        virtual std::shared_ptr<Mesh> get_mesh() const = 0;

        void set_material(const std::shared_ptr<Material>& value);
        std::shared_ptr<Material> get_material() const;

    private:
        bool                      visible;
        bool                      collidable;
        std::shared_ptr<Material> material;
    };
}
