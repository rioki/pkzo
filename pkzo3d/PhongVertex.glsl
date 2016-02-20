#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

layout(location = 0) in vec4 aVertex;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec2 aTangent;
layout(location = 4) in vec3 aColor;

void main()
{   
    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * aVertex;
}