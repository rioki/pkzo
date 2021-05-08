// Ice Engine
// Copyright 2020 Sean Farrell
// All rights reserved.

#version 430

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;

in vec3 pkzo_Vertex;
in vec3 pkzo_Normal;
in vec2 pkzo_TexCoord;

out vec3 vPosition;
out vec3 vCamera;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
    mat4 viewInv = inverse(pkzo_ViewMatrix);
    vCamera     = vec3(viewInv[3]);
    vPosition   = vec3(pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0));
    vNormal     = mat3(pkzo_ModelMatrix) * pkzo_Normal;
    vTexCoord   = pkzo_TexCoord;
    gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0);
}
