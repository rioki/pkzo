// Ice Engine
// Copyright 2020 Sean Farrell
// All rights reserved.

#version 430

// Material
uniform sampler2D pkzo_DiffuseMap;
uniform sampler2D pkzo_SpecularMap;
uniform sampler2D pkzo_RoughtnessMap;

// Light
#define AMBIENT_LIGHT     0
#define DIRECTIONAL_LIGHT 1
#define POINT_LIGHT       2
#define SPOT_LIGHT        3
#define ATTENUATION_FACTOR_LIN 1.0
#define ATTENUATION_FACTOR_QUAD 1.0
uniform int   pkzo_LightType;
uniform vec3  pkzo_LightColor;
uniform vec3  pkzo_LightDirection;
uniform vec3  pkzo_LightPosition;
uniform float pkzo_LightInnerAngle;
uniform float pkzo_LightOuterAngle;

// Inputs
in vec3 vPosition;
in vec3 vCamera;
in vec3 vNormal;
in vec2 vTexCoord;

// Outputs
out vec4 pkzo_FragColor;

vec3 getDiffuse()
{
    return texture(pkzo_DiffuseMap, vTexCoord).rgb;
}

vec3 getSpecular()
{
    return texture(pkzo_SpecularMap, vTexCoord).rgb;
}

float getRoughtnes()
{
    return texture(pkzo_RoughtnessMap, vTexCoord).r;
}

vec3 getNormal()
{
    return normalize(vNormal);
}

vec3 getLightColor()
{
    return pkzo_LightColor;
}

vec3 getLightDirection()
{
    switch (pkzo_LightType)
    {
        case DIRECTIONAL_LIGHT:
            return normalize(-pkzo_LightDirection);
        case POINT_LIGHT:
        case SPOT_LIGHT:
            return pkzo_LightPosition - vPosition;
    }
}

vec3 getEyeVector()
{
    return normalize(vPosition - vCamera);
}

float getLightAttenuation(vec3 lightDir)
{
    switch (pkzo_LightType)
    {
        case DIRECTIONAL_LIGHT:
            return 1.0;
        case POINT_LIGHT:
        {
            float d = length(lightDir);
            return 1.0/(1.0 + ATTENUATION_FACTOR_LIN * d + ATTENUATION_FACTOR_QUAD * pow(d, 2.0));
        }
        case SPOT_LIGHT:
        {
            float d = length(lightDir);
            float a = acos(dot(normalize(lightDir), normalize(-pkzo_LightDirection)));
            float dist_atten = 1.0/(1.0 + ATTENUATION_FACTOR_LIN * d + ATTENUATION_FACTOR_QUAD * pow(d, 2.0));
            return dist_atten * (smoothstep(pkzo_LightOuterAngle, pkzo_LightInnerAngle, a));
        }
    }
}

void main()
{
    if (pkzo_LightType == AMBIENT_LIGHT)
    {
        pkzo_FragColor = vec4(getDiffuse() * pkzo_LightColor, 1.0);
        return;
    }

    vec3  result   = vec3(0.0);
    vec3  normal   = getNormal();
    vec3  lightDir = getLightDirection();
    float atten    = getLightAttenuation(lightDir);
    vec3  eye      = getEyeVector();
    vec3  lColor   = getLightColor();

    float NdL = clamp(dot(normal, normalize(lightDir)), 0.0, 1.0);
    result = NdL * getDiffuse() * lColor * atten;

    vec3 refl = reflect(lightDir, normal);
    float RdE = clamp(dot(refl, eye), 0.0, 1.0);

    float shiny = 1.0 - getRoughtnes();
    float fs = pow(RdE, 128.0 * shiny);
    result += fs * getSpecular() * lColor * atten;

    pkzo_FragColor = vec4(result, 1.0);
}
