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
	ws_Normal = mat3(pkzo_ModelMatrix) * pkzo_Normal;
	gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * vec4(ws_Position, 1.0);
}
#endif

#ifdef PKZO_FRAGMENT_CODE

uniform vec3 Albedo;
uniform float Roughtness;
uniform float Metal;

#define PKZO_AMBIENT_LIGHT 0
#define PKZO_DIRECTIONAL_LIGHT 1
#define PKZO_POINT_LIGHT 2
#define PKZO_SPOT_LIGHT 3
uniform int pkzo_LightType;
uniform vec3 pkzo_LightColor;
uniform vec3 pkzo_LightPosition;
uniform vec3 pkzo_LightDirection;
uniform float pkzo_LightAngle;

in vec3 ws_Position;
in vec3 ws_Normal;

out vec4 pkzo_FragColor;

void main()
{
	switch (pkzo_LightType)
	{
		case PKZO_AMBIENT_LIGHT:
			pkzo_FragColor = vec4(Albedo * pkzo_LightColor, 1.0);
			break;
		case PKZO_DIRECTIONAL_LIGHT:
			pkzo_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
			break;
		case PKZO_POINT_LIGHT:
			pkzo_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
			break;
		case PKZO_SPOT_LIGHT:
			pkzo_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
			break;
	}
}

#endif
