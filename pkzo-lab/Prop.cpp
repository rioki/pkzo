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

#include "Prop.h"

#include "env.h"

namespace lab
{
    Prop::Prop(Init init)
    : Body({init.parent, init.transform, init.mass})
    {
        // All polyhaven models are Y top, not Z top
        auto is_polyhaven = init.model.find("polyhaven") != std::string::npos;
        auto transform = is_polyhaven ? glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0)) : glm::mat4(1.0);
        auto collision = (is_polyhaven && init.collision == Prop::Collision::BOUNDING_CYLINER_Z) ? Prop::Collision::BOUNDING_CYLINER_Y : init.collision;

        auto model = pkzo::Model::load(get_asset_folder() / init.model);
        add<pkzo::ModelInstance>({
            .transform = transform,
            .model     = model,
            .collision = collision
        });
    }
}