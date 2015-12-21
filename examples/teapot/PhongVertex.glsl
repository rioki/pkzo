#version 400

uniform mat4 uProjection;
uniform mat4 uModelView;

in vec3 aVertex;
in vec4 aColor;

out vec4 vColor;

void main()
{	
    vColor      = aColor;
    gl_Position = uProjection * uModelView * vec4(aVertex, 1.0);
}
