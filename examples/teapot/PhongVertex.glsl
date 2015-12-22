#version 400

uniform mat4 uProjection;
uniform mat4 uModelView;

in vec3 aVertex;
in vec2 aTexCoord;
in vec4 aColor;

out vec2 vTexCoord;
out vec4 vColor;

void main()
{	
	vTexCoord   = aTexCoord;
    vColor      = aColor;
    gl_Position = uProjection * uModelView * vec4(aVertex, 1.0);
}
