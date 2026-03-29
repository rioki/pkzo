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

#include <string>
#include <string_view>

#include "api.h"

namespace pkzo
{
    constexpr int MAX_LIGHTS = 4;
    constexpr int MAX_LIGHT_PROBES = 1;

    enum class UniformLocation : int
    {
        // Tansforms
        PROJECTION_MATRIX,
        VIEW_MATRIX,
        MODEL_MATRIX,
        // Material
        BASE_COLOR_FACTOR,
        BASE_COLOR_MAP,
        METALLIC_FACTOR,
        ROUGHNESS_FACTOR,
        METALLIC_ROUGHNESS_MAP,
        NORMAL_MAP,
        EMISSIVE_FACTOR,
        EMISSIVE_MAP,
        // Light
        LIGHT0_TYPE,
        LIGHT0_DIRECTION,
        LIGHT0_POSITION,
        LIGHT0_COLOR,
        LIGHT0_ANGLES,
        LIGHT1_TYPE,
        LIGHT1_DIRECTION,
        LIGHT1_POSITION,
        LIGHT1_COLOR,
        LIGHT1_ANGLES,
        LIGHT2_TYPE,
        LIGHT2_DIRECTION,
        LIGHT2_POSITION,
        LIGHT2_COLOR,
        LIGHT2_ANGLES,
        LIGHT3_TYPE,
        LIGHT3_DIRECTION,
        LIGHT3_POSITION,
        LIGHT3_COLOR,
        LIGHT3_ANGLES,
        SHADOW_MAP,
        // SkyBox & Light Probes
        ENVIRONMENT,
        LIGHT_PROBE0_ENABLED,
        LIGHT_PROBE0_ENVIRONMENT,
        LIGHT_PROBE0_DIFFUSE,
        LIGHT_PROBE0_SPECULAR,
        // Cubemap/Texture Generator & Filter
        MIPLEVEL,
        TEXTURE,
        CUBEMAP,
        CUBEMAP_TBN
    };

    class PKZO_EXPORT Shader
    {
    public:
        struct Source
        {
            std::string vertex;
            std::string fragment;
        };

        virtual ~Shader() = default;

        virtual int get_uniform_location(const std::string_view name) const = 0;
        virtual int get_attribute_location(const std::string_view name) const = 0;
    };
}
