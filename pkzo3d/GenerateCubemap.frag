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

#version 430 core

#include "uniforms.glsl"
#include "outputs.glsl"
#include "math.glsl"

in vec3 var_Direction;

vec2 inverseDirection(vec3 direction)
{
    vec2 spherical = cartesianToSpherical(normalize(direction));
    float u = 0.5 + spherical.x / (2.0 * PI);
    float v = 0.5 - spherical.y / (PI);
    return vec2(u, v);
}

void main()
{
    vec3 direction = normalize(var_Direction);
    vec2 uv        = inverseDirection(direction);

    uv.x = 0.5 + atan(direction.x, direction.y) / (2.0 * PI);
    uv.y = 0.5 + asin(direction.z) / PI;

    out_FragColor0 = texture(uni_Texture, uv);
}
