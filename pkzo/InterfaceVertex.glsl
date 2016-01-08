#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;

in vec3 aVertex;
in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{	
	vTexCoord   = aTexCoord;
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertex, 1.0);
}
