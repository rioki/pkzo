// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifdef PKZO_VERTEX_CODE

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;
uniform mat3 pkzo_TextureMatrix;

in vec3 pkzo_Vertex;
in vec2 pkzo_TexCoord; 

out vec2 texcoords;

void main()
{
	texcoords = vec2(pkzo_TextureMatrix * vec3(pkzo_TexCoord, 1.0));
	gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform sampler2D Texture;
uniform vec4 Color;

in vec2 texcoords;

out vec4 pkzo_FragColor;

void main()
{
	pkzo_FragColor = texture(Texture, texcoords) * Color;
}
#endif
