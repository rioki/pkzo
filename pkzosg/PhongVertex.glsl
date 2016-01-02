#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelViewMatrix;

in vec3 aVertex;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vNormal;
out vec2 vTexCoord;

void main()
{	
	// TODO uniform
	mat3 normalMatrix = mat3(uViewMatrix);

	vNormal     = normalMatrix * aNormal;
	vTexCoord   = aTexCoord;
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertex, 1.0);
}
