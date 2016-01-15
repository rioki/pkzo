#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform mat3 uNormalMatrix;

in vec3 aVertex;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vNormal;
out vec2 vTexCoord;

void main()
{  
    vNormal     = uNormalMatrix * aNormal;
    vTexCoord   = aTexCoord;
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertex, 1.0);
}
