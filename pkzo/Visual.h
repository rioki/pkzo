// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "config.h"

#include "SceneNode.h"

namespace pkzo
{
    class Renderer;
    class Material;
    class Mesh;

    class ICE_EXPORT Visual : public SceneNode
    {
    public:
        static std::shared_ptr<Material> get_default_material() noexcept;

        Visual(const glm::mat4& transform, const std::shared_ptr<const Mesh>& mesh, const std::shared_ptr<const Material>& material, const glm::vec3& local_scale = glm::vec3(1.0f)) noexcept;

        const std::shared_ptr<const Mesh>& get_mesh() const noexcept;

        void set_material(const std::shared_ptr<const Material>& value);
        const std::shared_ptr<const Material>& get_material() const noexcept;

        void activate() override;
        void deactivate() override;

    protected:
        void set_mesh(const std::shared_ptr<const Mesh>& value);

        const glm::vec3& get_local_scale() const noexcept;
        void set_local_scale(const glm::vec3& value) noexcept;

    private:
        std::shared_ptr<const Mesh>     mesh;
        std::shared_ptr<const Material> material;
        glm::vec3                       local_scale;

        Renderer* renderer = nullptr;
        unsigned int render_handle = 0;
    };
}
