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

#include <filesystem>
#include <vector>

#include <glm/glm.hpp>

#include <pkzo/Texture.h>
#include <pkzo/Mesh.h>

#include "api.h"
#include "Material.h"
#include "Scene.h"

namespace pkzo
{
    using pkzo::Texture;
    using pkzo::Mesh;

    class PKZO_EXPORT Model
    {
    public:
        struct Node
        {
            glm::mat4                          transform = glm::mat4(1.0f);
            std::shared_ptr<Material>          material;
            std::shared_ptr<Mesh>              mesh;
            std::vector<std::unique_ptr<Node>> children;
        };

        static std::shared_ptr<Model> load(const std::filesystem::path& file);

        Model(const std::filesystem::path& file);
        ~Model();

        void instantiate(SceneGroup& group, bool collidable = true) const;

    private:
        std::unique_ptr<Node> root_node;


        Model(const Model&) = delete;
        Model& operator = (const Model&) = delete;
    };
}
