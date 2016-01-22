#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

layout(location = 0) in vec4 aVertex;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec2 aTangent;
layout(location = 4) in vec3 aColor;

out vec3 vTexCoord;

void main()
{
    mat4 r = uViewMatrix;
    r[3][0] = 0.0;
    r[3][1] = 0.0;
    r[3][2] = 0.0;
    
    vec4 v = inverse(r) * inverse(uProjectionMatrix) * aVertex;

    vTexCoord    = v.xyz; 
    gl_Position  = aVertex;
}
