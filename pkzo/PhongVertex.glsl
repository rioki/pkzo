#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uModelViewMatrix;

uniform vec3      uCameraPosition;

layout(location = 0) in vec4 aVertex;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec2 aTangent;
layout(location = 4) in vec3 aColor;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vEye;

void main()
{   
    vPosition   = vec3(uModelMatrix  * aVertex);
    vNormal     = mat3(uModelMatrix) * aNormal;
    vEye        = uCameraPosition - vPosition;
    vTexCoord   = aTexCoord;
    gl_Position = uProjectionMatrix * uModelViewMatrix * aVertex;
}
