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

// This file is generated, do not edit.

#define MAX_LIGHTS 4
#define NONE_LIGHT 0
#define AMBIENT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define POINT_LIGHT 3
#define SPOT_LIGHT 4

#define MAX_LIGHT_PROBES 1

#define XPOS 0
#define XNEG 1
#define YPOS 2
#define YNEG 3
#define ZPOS 4
#define ZNEG 5

struct Light
{
    int type;
    vec3 direction;
    vec3 position;
    vec3 color;
    vec2 angles;
};

struct LightProbe
{
    int enabled;
    samplerCube environment;
    samplerCube diffuse;
    samplerCube specular;
};

layout(location = 0) uniform mat4 uni_ProjectionMatrix;
layout(location = 1) uniform mat4 uni_ViewMatrix;
layout(location = 2) uniform mat4 uni_ModelMatrix;
layout(location = 3) uniform vec4 uni_BaseColorFactor;
layout(location = 4) uniform sampler2D uni_BaseColorMap;
layout(location = 5) uniform float uni_MetallicFactor;
layout(location = 6) uniform float uni_RoughnessFactor;
layout(location = 7) uniform sampler2D uni_MetallicRoughnessMap;
layout(location = 8) uniform sampler2D uni_NormalMap;
layout(location = 9) uniform vec3 uni_EmissiveFactor;
layout(location = 10) uniform sampler2D uni_EmissiveMap;
layout(location = 11) uniform Light uni_Light[4];
layout(location = 31) uniform sampler2D uni_ShadowMap;
layout(location = 32) uniform samplerCube uni_Environment;
layout(location = 33) uniform LightProbe uni_LightProbes[1];
layout(location = 37) uniform int uni_MipLevel;
layout(location = 38) uniform sampler2D uni_Texture;
layout(location = 39) uniform samplerCube uni_CubeMap;
layout(location = 40) uniform mat3 uni_CubemapTBN;
