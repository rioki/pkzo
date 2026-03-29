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

#include "Geometry.h"

namespace pkzo
{
    class PKZO_EXPORT CylinderGeometry : public Geometry
    {
    public:
        struct Init
        {
            Node*                     parent        = nullptr;
            glm::mat4                 transform     = glm::mat4(1.0f);
            bool                      visible       = true;
            bool                      collidable    = true;
            float                     diameter      = 1.0f;
            float                     height        = 1.0f;
            unsigned int              sectors       = 16u;
            std::shared_ptr<Material> material;
        };

        CylinderGeometry(Init init);

        ~CylinderGeometry();

        float get_diameter() const;
        void set_diameter(float value);

        float get_height() const;
        void set_height(float value);

        unsigned int get_sectors() const;

        Bounds get_bounds() const override;

        std::shared_ptr<Mesh> get_mesh() const override;

    private:
        float           diameter;
        float           height;
        unsigned int    sectors;

        mutable std::shared_ptr<Mesh> mesh;
    };
}
