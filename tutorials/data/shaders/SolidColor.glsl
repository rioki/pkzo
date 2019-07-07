// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifdef PKZO_VERTEX_CODE

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;

in vec3 pkzo_Vertex;

void main()
{
	gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform vec4 Color;

out vec4 pkzo_FragColor;

void main()
{
	pkzo_FragColor = Color;
}
#endif
