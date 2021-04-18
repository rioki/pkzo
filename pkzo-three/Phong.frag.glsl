// Ice Engine
// Copyright 2020 Sean Farrell
// All rights reserved.

#version 430

uniform vec4      pkzo_BaseColorFactor;
uniform bool      pkzo_HasBaseColorMap;
uniform sampler2D pkzo_BaseColorMap;

#define AMBIENT_LIGHT     0
#define DIRECTIONAL_LIGHT 1
#define POINT_LIGHT       2
#define SPOT_LIGHT        3
uniform int  pkzo_LightType;
uniform vec3 pkzo_LightColor;
uniform vec3 pkzo_LightDirection;
uniform vec3 pkzo_LightPosition;
uniform vec3 pkzo_LightAngle;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 pkzo_FragColor;

vec4 getBaseColor()
{
    if (pkzo_HasBaseColorMap)
    {
        return texture(pkzo_BaseColorMap, vTexCoord) * pkzo_BaseColorFactor;
    }
    else
    {
        return pkzo_BaseColorFactor;
    }
}

vec3 getNormal()
{
    return normalize(vNormal);
}

vec3 getLightDirection()
{
    switch (pkzo_LightType)
    {
        case DIRECTIONAL_LIGHT:
            return normalize(-pkzo_LightDirection);
        case POINT_LIGHT:
        case SPOT_LIGHT:
            return normalize(vPosition - pkzo_LightPosition);
    }
}

void main()
{
    if (pkzo_LightType == AMBIENT_LIGHT)
    {
        pkzo_FragColor = getBaseColor() * vec4(pkzo_LightColor, 1.0f);
        return;
    }

    vec3 normal    = getNormal();
    vec3 lightDir  = getLightDirection();
    float NdL = dot(normal, lightDir);
    if (NdL > 0.0)
    {
        vec3 result    = vec3(0.0);
        vec4 baseColor = getBaseColor();

        // TODO attenuation
        result = NdL * baseColor.rgb * pkzo_LightColor;

        // TODO specular
        pkzo_FragColor = vec4(result, baseColor.a);
    }
    //pkzo_FragColor = vec4(normal * vec3(0.5) + vec3(0.5), 1.0);
    //pkzo_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
