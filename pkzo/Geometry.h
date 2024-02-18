// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <memory>

#include "defines.h"
#include "SceneNode.h"
#include "Material.h"

namespace pkzo
{
    class PKZO_EXPORT Geometry : public SceneNode
    {
    public:
        Geometry();
        Geometry(glm::mat4 transform, const std::shared_ptr<Material>& material);
        Geometry(const Geometry& other);
        ~Geometry();

        void serialize(nlohmann::json& j, const std::filesystem::path& base_dir) const override;
        void deserialize(const nlohmann::json& j, const std::filesystem::path& base_dir) override;

        void activate() override;
        void deactivate() override;

        void set_material(const std::shared_ptr<Material>& material);
        std::shared_ptr<Material> get_material() const;

    protected:
        unsigned int gid = 0;

        virtual void attach_graphics() = 0;
        virtual void sync_graphics() = 0;

    private:
        std::shared_ptr<Material> material;
    };


}
