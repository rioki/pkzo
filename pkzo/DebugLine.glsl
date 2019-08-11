// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifdef PKZO_VERTEX_CODE

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;

uniform vec3 uStart;
uniform vec3 uEnd;

in vec2 pkzo_TexCoord;

out vec2 vTexCoord;

void main()
{
	vTexCoord = pkzo_TexCoord;
	vec3 vertex = gl_VertexID == 0 ? uStart : uEnd;
	gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * vec4(vertex, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform vec4 uStartColor;
uniform vec4 uEndColor;

in vec2 vTexCoord;

out vec4 pkzo_FragColor;

void main()
{
	//pkzo_FragColor = mix(uStartColor, uEndColor, vTexCoord.x);
	pkzo_FragColor = vec4(1, 0, 0, 1);
}

#endif
