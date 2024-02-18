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

#version 430

uniform vec4      uBaseColorFactor;
uniform bool      uHasBaseColorMap;
uniform sampler2D uBaseColorMap;
uniform float     uMetallicFactor;
uniform float     uRoughnessFactor;
uniform bool      uHasMetallicRoughnessMap;
uniform sampler2D uMetallicRoughnessMap;
uniform vec3      uEmissiveFactor;
uniform bool      uHasEmissiveMap;
uniform sampler2D uEmissiveMap;
uniform bool      uHasNormalMap;
uniform sampler2D uNormalMap;

in vec3 vPosition;
in mat3 vTBN;
in vec2 vTexCoord;

out vec4 oPosition;
out vec4 oNormal;
out vec4 oBaseColor;
out vec4 oMRHA;
out vec4 oEmissive;

vec4 getBaseColor()
{
    vec4 color = uBaseColorFactor;
    if (uHasBaseColorMap)
    {
        color *= texture(uBaseColorMap, vTexCoord);
    }
    return color;
}

vec3 getNormal()
{
    vec3 normal = normalize(vTBN * vec3(0.0, 0.0, 1.0));
    if (uHasNormalMap)
    {
        normal = normalize(vTBN * (texture(uNormalMap, vTexCoord).xyz * 2.0 - 1.0));
    }
    return normal;
}

vec4 getMRHA()
{
    vec4 mrhao = vec4(uRoughnessFactor, uMetallicFactor, 0.0, 0.0);
    if (uHasMetallicRoughnessMap)
    {
        mrhao = texture(uMetallicRoughnessMap, vTexCoord);
    }
    return mrhao;
}

vec3 getEmissive()
{
    vec3 emissive = uEmissiveFactor;
    if (uHasEmissiveMap)
    {
        emissive *= texture(uEmissiveMap, vTexCoord).rgb;
    }
    return emissive;
}


void main()
{
    oPosition  = vec4(vPosition, 1.0);
    oNormal    = vec4(getNormal(), 1.0);
    oBaseColor = getBaseColor();
    oMRHA      = getMRHA();
    oEmissive  = vec4(getEmissive(), 1.0);
}
