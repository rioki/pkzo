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

#include "ModelInstance.h"

#include <pkzo/debug.h>

#include "BoxGeometry.h"
#include "SphereGeometry.h"
#include "CylinderGeometry.h"

namespace pkzo
{
    using pkzo::check;

    ModelInstance::ModelInstance(Init init)
    : Group({init.parent, init.transform})
    {
        check(init.model, "Model is null");

        bool model_is_collidable = init.collision == Collision::MESH;

        init.model->instantiate(*this, model_is_collidable);

        if (init.collision == Collision::BOUNDING_BOX)
        {
            auto bounds = get_bounds();
            add<BoxGeometry>({
                .transform  = position(bounds.get_center()),
                .visible    = false,
                .collidable = true,
                .size       = bounds.get_size()
            });
        }
        if (init.collision == Collision::BOUNDING_SPHERE)
        {
            auto bounds   = get_bounds();
            auto size     = bounds.get_size();
            auto diameter = std::max(std::max(size.x, size.y), size.z);
            add<SphereGeometry>({
                .transform  = position(bounds.get_center()),
                .visible    = false,
                .collidable = true,
                .diameter   = diameter
            });
        }
        if (init.collision == Collision::BOUNDING_CYLINER_X)
        {
            auto bounds    = get_bounds();
            auto size      = bounds.get_size();
            auto diameter  = std::max(size.y, size.z);
            auto height    = size.x;
            auto transform = position(bounds.get_center());
                 transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            add<CylinderGeometry>({
                .transform  = transform,
                .visible    = false,
                .collidable = true,
                .diameter   = diameter,
                .height     = height
            });
        }
        if (init.collision == Collision::BOUNDING_CYLINER_Y)
        {
            auto bounds   = get_bounds();
            auto size     = bounds.get_size();
            auto diameter = std::max(size.x, size.z);
            auto height   = size.y;
            auto transform = position(bounds.get_center());
                 transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            add<CylinderGeometry>({
                .transform  = transform,
                .visible    = false,
                .collidable = true,
                .diameter   = diameter,
                .height     = height
            });
        }
        if (init.collision == Collision::BOUNDING_CYLINER_Z)
        {
            auto bounds   = get_bounds();
            auto size     = bounds.get_size();
            auto diameter = std::max(size.x, size.y);
            auto height   = size.z;
            add<CylinderGeometry>({
                .transform  = position(bounds.get_center()),
                .visible    = false,
                .collidable = true,
                .diameter   = diameter,
                .height     = height
            });
        }
    }
}
