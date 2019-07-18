// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifdef PKZO_VERTEX_CODE

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;

in vec3 pkzo_Vertex;
in vec3 pkzo_Normal;

out vec3 ws_Position;
out vec3 ws_Normal;

void main()
{
	ws_Position = (pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0)).xyz;
	ws_Normal = mat3(pkzo_ModelMatrix) * pkzo_Vertex;
	gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * vec4(ws_Position, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform vec3 Albedo;
uniform float Roughtness;
uniform float Metal;

in vec3 ws_Position;
in vec3 ws_Normal;
  
layout(location = 0) out vec4 pkzo_FragPosition;
layout(location = 1) out vec4 pkzo_FragNormal; 
layout(location = 2) out vec4 pkzo_FragAlbedo;
layout(location = 3) out vec4 pkzo_FragRMHAO;

void main()
{
	pkzo_FragPosition = vec4(ws_Position, 1.0);
	pkzo_FragNormal = vec4(ws_Normal, 1.0);
	pkzo_FragAlbedo = vec4(Albedo, 1.0);
	pkzo_FragRMHAO = vec4(Roughtness, Metal, 0.0, 1.0);
}
#endif
