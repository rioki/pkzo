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

#include <filesystem>

#include "defines.h"
#include "Group.h"

namespace pkzo
{
    class Renderer;

    class PKZO_EXPORT Scene : public Group
    {
    public:
        Scene();
        Scene(const std::filesystem::path& file);
        Scene(const Scene& other);
        ~Scene();

        const std::filesystem::path& get_file() const noexcept;

        std::string get_type() const noexcept override;
        std::unique_ptr<SceneNode> clone() const noexcept override;

        bool is_active() const noexcept override;
        void activate() override;
        void deactivate() override;

        void save(const std::filesystem::path& path) const;

        Renderer& get_renderer();

        void draw(glm::uvec2 resolution) const;

    private:
        bool active = false;
        std::filesystem::path file;
        std::unique_ptr<Renderer> renderer;
    };


}
