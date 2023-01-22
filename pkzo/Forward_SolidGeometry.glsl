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

#ifdef GLOW_VERTEX

uniform mat4 glow_ProjectionMatrix;
uniform mat4 glow_ViewMatrix;
uniform mat4 glow_ModelMatrix;

in vec3 glow_Vertex;
in vec3 glow_Normal;
in vec2 glow_TexCoord;

out vec3 var_Position;
out vec3 var_Normal;
out vec2 var_TexCoord;

void main()
{
    var_Position = vec3(glow_ModelMatrix * vec4(glow_Vertex, 1.0));
    var_Normal   = mat3(glow_ModelMatrix) * glow_Normal;
    var_TexCoord = glow_TexCoord;
    gl_Position  = glow_ProjectionMatrix * glow_ViewMatrix * glow_ModelMatrix * vec4(glow_Vertex, 1.0);
}

#endif

#ifdef GLOW_FRAGMENT

#define ATTENUATION_FACTOR_LIN 1.0
#define ATTENUATION_FACTOR_QUAD 1.0

uniform vec4      ice_BaseColorFactor;
uniform sampler2D ice_BaseColorMap;

#define AMBIENT_LIGHT     0
#define DIRECTIONAL_LIGHT 1
#define POINT_LIGHT       2
#define SPOT_LIGHT        3

uniform int       ice_LightType;
uniform vec3      ice_LightColor;
uniform vec3      ice_LightDirection;
uniform vec3      ice_LightPosition;
uniform float     ice_LightInnerAngle;
uniform float     ice_LightOuterAngle;

in vec3 var_Position;
in vec3 var_Normal;
in vec2 var_TexCoord;

out vec4 glow_FragColor;

vec3 phong(vec3 n, vec3 l, vec3 mc, vec3 lc, float a)
{
    // just N*L for now
    float df = clamp(dot(n, l), 0.0, 1.0);
    return df * mc * lc * a;
}

void main()
{
    vec3  color     = vec3(0.0, 0.0, 0.0);
    vec3  n;
    vec3  l;
    float d;
    float a;

    vec4 baseColor = texture(ice_BaseColorMap, var_TexCoord) * ice_BaseColorFactor;

    switch (ice_LightType)
    {
        case AMBIENT_LIGHT:
            color = baseColor.rgb * ice_LightColor;
            break;
        case DIRECTIONAL_LIGHT:
            n = normalize(var_Normal);
            l = normalize(-ice_LightDirection);
            a = 1.0;
            color = phong(n, l, baseColor.rgb, ice_LightColor, a);
            break;
        case POINT_LIGHT:
            n = normalize(var_Normal);
            l = ice_LightPosition - var_Position;
            d = length(l);
            l       = normalize(l);
            a = 1.0/(1.0 + ATTENUATION_FACTOR_LIN * d + ATTENUATION_FACTOR_QUAD * pow(d, 2.0));
            color = phong(n, l, baseColor.rgb, ice_LightColor, a);
            break;
        case SPOT_LIGHT:
            n = normalize(var_Normal);
            l = ice_LightPosition - var_Position;
            d = length(l);
            l       = normalize(l);
            float da = 1.0/(1.0 + ATTENUATION_FACTOR_LIN * d + ATTENUATION_FACTOR_QUAD * pow(d, 2.0));
            float phi  = acos(dot(l, normalize(-ice_LightDirection)));
            a  = da * (1.0 - smoothstep(ice_LightInnerAngle, ice_LightOuterAngle, phi));
            color = phong(n, l, baseColor.rgb, ice_LightColor, a);
            break;
    }

    glow_FragColor = vec4(color, 1.0f);
}

#endif
