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

#define SAMPLES 1024

in vec3 var_Direction;

void main()
{
    vec3 normal = normalize(var_Direction);

    vec3 up = abs(normal.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
    vec3 right = normalize(cross(up,normal));
    up = cross(normal,right);

    mat3 tbn = mat3(right, up, normal);

    vec3  color = vec3(0);
    float power = 0;

    for (int i = 0; i < SAMPLES; i++)
    {
        vec2 s = hammersley2d(i, SAMPLES);
        vec3 l = hemisphereSample_cos(s.x, s.y);
        l = tbn * l;
        float NxL = dot(normal, l);

        vec3 smp = texture(uni_CubeMap, l).rgb;
        float lum = dot(smp, vec3(0.2126, 0.7152, 0.0722));
        float limit = 10.0;

        if (lum > limit)
        {
            float compressed = limit + log(1.0 + lum - limit);
            smp *= compressed / lum;
        }
        color += smp * NxL;
        power += NxL;
    }

    out_FragColor0 = vec4(color / power, 1);
}
