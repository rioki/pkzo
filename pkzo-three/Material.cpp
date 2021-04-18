//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Material.h"

namespace pkzo::three
{
    void Material::set_base_color_factor(const glm::vec4& value) noexcept
    {
        base_color_factor = value;
    }

    const glm::vec4& Material::get_base_color_factor() const noexcept
    {
        return base_color_factor;
    }

    void Material::set_base_color_map(const std::shared_ptr<Texture>& value) noexcept
    {
        base_color_map = value;
    }

    const std::shared_ptr<Texture>& Material::get_base_color_map() const noexcept
    {
        return base_color_map;
    }

    std::shared_ptr<Parameters> Material::to_parameters() const noexcept
    {
        auto params = std::make_shared<Parameters>();

        params->set_value("pkzo_BaseColorFactor", base_color_factor);
        if (base_color_map)
        {
            params->set_value("pkzo_HasBaseColorMap", true);
            params->set_value("pkzo_BaseColorMap", base_color_map);
        }
        else
        {
            params->set_value("pkzo_HasBaseColorMap", false);
        }

        return params;
    }
}