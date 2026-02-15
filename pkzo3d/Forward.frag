// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#version 430 core

#include "uniforms.glsl"
#include "outputs.glsl"

#define MIPS    6

in vec2 var_TexCoord;
in vec3 var_CameraPos;
in vec3 var_Position;
in mat3 var_TBN;

vec3 tonemap(vec3 x)
{
    vec3 X = max(vec3(0.0), x - 0.004);
    vec3 result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
    return pow(result, vec3(2.2));
}

vec3 lightProbe(LightProbe probe, vec3 normal, vec3 view, vec3 diffuseColor, vec3 specularColor, float roughness)
{
    vec3  reflection = reflect(-view, normal);

    vec3 diffuse  = texture(probe.diffuse, normal).rgb * diffuseColor;

    vec3 specular;
    if (roughness < 0.1)
    {
        specular = textureLod(probe.environment, reflection, 0).rgb * specularColor;
    }
    else
    {
        specular = textureLod(probe.specular, reflection, roughness * MIPS).rgb * specularColor;
    }

    return diffuse + specular;
}

vec3 directionalLight(Light light, vec3 normal, vec3 view, vec3 diffuseColor, vec3 specularColor, float shininess)
{
    vec3 lightDir   = normalize(-light.direction);

    float NdotL      = max(dot(normal, lightDir), 0.0);
    vec3 diffuse     = diffuseColor * light.color * NdotL;

    vec3 halfway     = normalize(lightDir + view);
    float NdotH      = max(dot(normal, halfway), 0.0);
    vec3 specular    = pow(NdotH, shininess * 128.0) * specularColor * light.color;

    return diffuse + specular;
}

vec3 pointLight(Light light, vec3 normal, vec3 view, vec3 diffuseColor, vec3 specularColor, float shininess)
{
    vec3  lightDir   = light.position - var_Position;
    float dist       = length(lightDir);
          lightDir   = normalize(lightDir);

    float attenuation = 1.0 / (dist * dist);

    float NdotL      = max(dot(normal, lightDir), 0.0);
    vec3 diffuse     = diffuseColor * light.color * NdotL * attenuation;

    vec3 halfway     = normalize(lightDir + view);
    float NdotH      = max(dot(normal, halfway), 0.0);
    vec3 specular    = pow(NdotH, shininess * 128.0) * specularColor * light.color * attenuation;

    return diffuse + specular;
}

vec3 spotLight(Light light, vec3 normal, vec3 view, vec3 diffuseColor, vec3 specularColor, float shininess)
{
    vec3  lightDir   = light.position - var_Position;
    float dist       = length(lightDir);
          lightDir   = normalize(lightDir);

    float attenuation = 1.0 / (dist * dist);

    float theta       = dot(lightDir, -normalize(light.direction));
    float cos_inner   = cos(light.angles.x);
    float cos_outer   = cos(light.angles.y);
          attenuation = attenuation * clamp((theta - cos_outer) / (cos_inner - cos_outer), 0.0, 1.0);

    float NdotL      = max(dot(normal, lightDir), 0.0);
    vec3 diffuse     = diffuseColor * light.color * NdotL * attenuation;

    vec3 halfway     = normalize(lightDir + view);
    float NdotH      = max(dot(normal, halfway), 0.0);
    vec3 specular    = pow(NdotH, shininess * 128.0) * specularColor * light.color * attenuation;

    return diffuse + specular;
}

void main()
{
    vec4  baseColor     = texture(uni_BaseColorMap, var_TexCoord) * uni_BaseColorFactor;
    float roughness     = texture(uni_MetallicRoughnessMap, var_TexCoord).g * uni_RoughnessFactor;
    float metallic      = texture(uni_MetallicRoughnessMap, var_TexCoord).r * uni_MetallicFactor;
    vec3  emissive      = texture(uni_EmissiveMap, var_TexCoord).rgb * uni_EmissiveFactor;

    vec3 normal_map     = texture(uni_NormalMap, var_TexCoord).rgb;
    vec3 normal         = normalize(var_TBN * (normal_map * 2.0 - 1.0));
    vec3 view           = normalize(var_CameraPos - var_Position);

    vec3  diffuseColor  = mix(baseColor.rgb, vec3(0.0), metallic);
    vec3  specularColor = mix(vec3(0.04), baseColor.rgb, metallic);
    float shininess     = mix(2.0, 256.0, 1.0 - roughness);

    //out_FragColor0 = vec4(roughness, roughness, roughness, baseColor.w);
    //return;

    vec3 result = emissive;

    for (int i = 0; i < MAX_LIGHT_PROBES; i++)
    {
        result += lightProbe(uni_LightProbes[i], normal, view, diffuseColor, specularColor, roughness);
    }

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        switch (uni_Light[i].type)
        {
            case NONE_LIGHT:
                break;
            case AMBIENT_LIGHT:
                result += baseColor.rgb * uni_Light[i].color;
                break;
            case DIRECTIONAL_LIGHT:
                result += directionalLight(uni_Light[i], normal, view, diffuseColor, specularColor, shininess);
                break;
            case POINT_LIGHT:
                result += pointLight(uni_Light[i], normal, view, diffuseColor, specularColor, shininess);
                break;
            case SPOT_LIGHT:
                result += spotLight(uni_Light[i], normal, view, diffuseColor, specularColor, shininess);
                break;
        }
    }

    result = tonemap(result);

    out_FragColor0 = vec4(result, baseColor.w);
}
