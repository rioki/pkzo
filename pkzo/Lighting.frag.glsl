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

#define AMBIENT_LIGHT     0
#define DIRECTIONAL_LIGHT 1
#define POINT_LIGHT       2
#define SPOT_LIGHT        3

uniform int   uLightType;
uniform int   uLightId;
uniform vec3  uLightColor;
uniform vec3  uLightDirection;
uniform vec3  uLightPosition;
uniform float uLightRadius;
uniform float uLightAngle;

uniform sampler2D uPosition;
uniform sampler2D uNormal;
uniform sampler2D uBaseColor;
uniform sampler2D uMRHA;
uniform sampler2D uDepth;

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 oFragColor;

void main()
{
    float depth = texture(uDepth, vTexCoord).x;
    if (depth == 1.0)
    {
        discard;
    }

    // geometry
    vec3  position   = texture(uPosition, vTexCoord).xyz;
    vec3  normal     = texture(uNormal,   vTexCoord).xyz;

    // material
    vec3  baseColor  = texture(uBaseColor, vTexCoord).rgb;
    float roughness  = texture(uMRHA, vTexCoord).y;
    float metal      = texture(uMRHA, vTexCoord).x;
    float shininess  = 1.0 - roughness;
    vec3  diffColor  = mix(baseColor, vec3(0), metal);
    vec3  specColor  = mix(vec3(1), baseColor, metal);

    vec3 color = vec3(1.0);
    switch (uLightType)
    {
        case AMBIENT_LIGHT:
            color = baseColor * uLightColor;
            break;
        case DIRECTIONAL_LIGHT:
        {
            vec3 light  = normalize(-uLightDirection);
            float intensity = max(0.0, dot(normal, light));
            color = intensity * baseColor * uLightColor;
            break;
        }
        default:
            discard;
    }

    oFragColor = vec4(color, 1.0);
}
