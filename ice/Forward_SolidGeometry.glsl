// Ice Engine
// Copyright 2022 Sean Farrell
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

out vec3 var_Normal;
out vec2 var_TexCoord;

void main()
{
    var_Normal   = mat3(glow_ModelMatrix) * glow_Normal;
    var_TexCoord = glow_TexCoord;
    gl_Position  = glow_ProjectionMatrix * glow_ViewMatrix * glow_ModelMatrix * vec4(glow_Vertex, 1.0);
}

#endif

#ifdef GLOW_FRAGMENT

uniform vec3      mat_BaseColor;

#define AMBIENT_LIGHT     0
#define DIRECTIONAL_LIGHT 1

uniform int       lgt_Type;
uniform vec3      lgt_Color;
uniform vec3      lgt_Direction;
uniform vec3      lgt_Position;
uniform float     lgt_InnerAngle;
uniform float     lgt_OuterAngle;

in vec3 var_Normal;
in vec2 var_TexCoord;

out vec4 out_FragColor;

vec3 phong(vec3 n, vec3 l, vec3 mc, vec3 lc)
{
    // just N*L for now
    float df = clamp(dot(n, l), 0.0, 1.0);
    return df * mc * lc;
}

void main()
{
    vec3 color = vec3(0.0, 0.0, 0.0);

    switch (lgt_Type)
    {
        case AMBIENT_LIGHT:
            color = mat_BaseColor * lgt_Color;
            break;
        case DIRECTIONAL_LIGHT:
            vec3 n = normalize(var_Normal);
            vec3 l = normalize(-lgt_Direction);
            color = phong(n, l, mat_BaseColor, lgt_Color);
            break;
    }

    out_FragColor = vec4(color, 1.0f);
}

#endif
