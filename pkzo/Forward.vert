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

#include "attributes.glsl"
#include "uniforms.glsl"

out vec2 var_TexCoord;
out vec3 var_CameraPos;
out vec3 var_Position;
out mat3 var_TBN;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(uni_ModelMatrix)));
    vec3 normal      = normalize(normalMatrix * atr_Normal);
    vec3 tangent     = normalize(normalMatrix * atr_Tangent);
    vec3 bitangent   = cross(normal, tangent);
    var_TBN          = mat3(tangent, bitangent, normal);

    var_TexCoord     = atr_TexCoord;

    vec4 world_pos  = uni_ModelMatrix * vec4(atr_Vertex, 1.0);
    var_Position    = world_pos.xyz;

    var_CameraPos  = (inverse(uni_ViewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;

    gl_Position     = uni_ProjectionMatrix * uni_ViewMatrix * world_pos;
}
