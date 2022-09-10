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
in vec2 glow_TexCoord;

out vec2 var_TexCoord;

void main()
{
    var_TexCoord = glow_TexCoord;
    gl_Position  = glow_ProjectionMatrix * glow_ViewMatrix * glow_ModelMatrix * vec4(glow_Vertex, 1.0);
}

#endif

#ifdef GLOW_FRAGMENT

uniform vec4      pkzo_Color;
uniform bool      pkzo_HasTexture;
uniform sampler2D pkzo_Texture;

in vec2 var_TexCoord;

out vec4 out_FragColor;

void main()
{
    if (pkzo_HasTexture)
    {
        out_FragColor = texture(pkzo_Texture, var_TexCoord) * pkzo_Color;
    }
    else
    {
        out_FragColor = pkzo_Color;
    }
}

#endif
