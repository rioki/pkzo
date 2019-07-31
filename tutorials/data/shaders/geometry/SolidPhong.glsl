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

vec3 shade_ambient_light(vec3 albedo)
{
	return albedo * pkzo_LightColor;
}

vec3 shade_directional_light(vec3 normal, vec3 albedo, float rougthness, float metal)
{
	float ndl = dot(normal, -pkzo_LightDirection); 
	if (ndl > 0.0)
	{
		return ndl * albedo * pkzo_LightColor;
	}
	return vec3(0.0);
}

vec3 shade_point_light(vec3 position, vec3 normal, vec3 albedo, float rougthness, float metal)
{
	vec3 light = pkzo_LightPosition - position;
	float dist = length(light);
	light = normalize(light);
	float ndl = dot(normal, light); 
	if (ndl > 0.0)
	{
		float att = 1.0 / (1.0 + 0.1*dist + 0.01*dist*dist);
		return att * ndl * albedo * pkzo_LightColor;
	}
	return vec3(0.0);
}

vec3 shade_spot_light(vec3 position, vec3 normal, vec3 albedo, float rougthness, float metal)
{
	vec3 light = pkzo_LightPosition - position;
	float dist = length(light);
	light = normalize(light);
	float ndl = dot(normal, light); 
	float ldd = dot(light, -pkzo_LightDirection);
	if (ndl > 0.0 && ldd > pkzo_LightAngle)
	{
		float att = 1.0 / (1.0 + 0.1*dist + 0.01*dist*dist);
		return att * ndl * albedo * pkzo_LightColor;
	}
	return vec3(0.0);
}

vec3 shade_light(vec3 position, vec3 normal, vec3 albedo, float rougthness, float metal)
{
	switch (pkzo_LightType)
	{
		case PKZO_AMBIENT_LIGHT:
			return shade_ambient_light(albedo);
		case PKZO_DIRECTIONAL_LIGHT:
			return shade_directional_light(normal, albedo, rougthness, metal);
		case PKZO_POINT_LIGHT:
			return shade_point_light(position, normal, albedo, rougthness, metal);
		case PKZO_SPOT_LIGHT:
			return shade_spot_light(position, normal, albedo, rougthness, metal);
	}
}

void main()
{
	vec3 normal = normalize(ws_Normal);
	vec3 color = shade_light(ws_Position, normal, Albedo, Roughtness, Metal);
	pkzo_FragColor = vec4(color, 1.0);
}

#endif
