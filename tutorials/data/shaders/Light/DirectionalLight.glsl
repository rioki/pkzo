// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifdef PKZO_VERTEX_CODE

in vec3 pkzo_Vertex;
in vec2 pkzo_TexCoord;

out vec2 ts_Texcoords;

void main()
{
	ts_Texcoords = pkzo_TexCoord;
	gl_Position = vec4(pkzo_Vertex, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform sampler2D pkzo_Depth;  
uniform sampler2D pkzo_Position;
uniform sampler2D pkzo_Normal;
uniform sampler2D pkzo_Albedo;
uniform sampler2D pkzo_RMHAO;

in vec2 ts_Texcoords;

out vec4 pkzo_FragColor;

void main()
{
	pkzo_FragColor = texture(pkzo_Albedo, ts_Texcoords);
}
#endif
