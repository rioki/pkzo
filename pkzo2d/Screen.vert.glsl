// Ice Engine
// Copyright 2020 Sean Farrell
// All rights reserved.

#version 430

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;

in vec3 pkzo_Vertex;
in vec2 pkzo_TexCoord;

out vec2 vTexCoord;

void main()
{
    vTexCoord = pkzo_TexCoord;
    gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0);
}
