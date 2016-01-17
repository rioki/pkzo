#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uModelViewMatrix;

uniform vec3      uCameraPosition;

in vec3 aVertex;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vEye;

void main()
{   
    vPosition   = vec3(uModelMatrix  * vec4(aVertex, 1.0));
    vNormal     = mat3(uModelMatrix) * aNormal;
    //vEye        = mat3(uViewMatrix)  * vec3(-1, -1, -1);
    //vEye        = -vec3(uModelViewMatrix  * vec4(aVertex, 1.0));
    vEye        = uCameraPosition - vPosition;
    vTexCoord   = aTexCoord;
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertex, 1.0);
}
