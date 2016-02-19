#version 400

#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

uniform vec3      uMaterialColor;
uniform float     uMaterialRoughness;
uniform bool      uMaterialHasTexture;
uniform sampler2D uMaterialTexture;

uniform int       uLightType;
uniform vec3      uLightDirection;
uniform vec3      uLightPosition;
uniform float     uLightRange;
uniform float     uLightCutoff;
uniform vec3      uLightColor;

in  vec3 vPosition;
in  vec3 vNormal;
in  vec2 vTexCoord;
in  vec3 vEye;

out vec4 oFragColor;

void main()
{
    vec3 result = vec3(0);
    vec3 materialColor = uMaterialColor;
    if (uMaterialHasTexture)
    {
        materialColor *= texture(uMaterialTexture, vTexCoord).rgb;
    }

  
    if (uLightType == AMBIENT_LIGHT)
    {
        result = materialColor * uLightColor;
    }
    else
    {
        vec3 lightDirection;
        float atten;
        if (uLightType == DIFFUSE_LIGHT) 
        {
            lightDirection = normalize(uLightDirection);
            atten = 1.0;
        }

        if (uLightType == POINT_LIGHT) 
        {
            lightDirection = uLightPosition - vPosition;
            float dist = length(lightDirection);
            if (dist > uLightRange) 
            {
                discard;
            }

            lightDirection = normalize(lightDirection);
            atten = 1.0 - (dist / uLightRange);
        }

        if (uLightType == SPOT_LIGHT) 
        {
            lightDirection = uLightPosition - vPosition;
            float dist = length(lightDirection);
            if (dist > uLightRange) 
            {
                discard;
            }

            lightDirection = normalize(lightDirection);
            atten = 1.0 - (dist / uLightRange);

            if (dot(lightDirection, uLightDirection) < uLightCutoff) 
            {
                atten = 1.0;
                discard;
            }
        }
    
        vec3  normal = normalize(vNormal);
        float nDotL  = dot(lightDirection, normal);
        if (nDotL > 0.0)
        {
            result += nDotL * materialColor * uLightColor * atten;

            float shininess = 1.0 - uMaterialRoughness;

            vec3 eye = normalize(vEye);
            vec3 reflection = reflect(normal, lightDirection);
            
            float intensity = max(dot(normal, lightDirection), 0.0);
            if (intensity > 0.0)
            {
                vec3 halfvector = normalize(lightDirection + eye);                 
                float intSpec = max(dot(halfvector, normal), 0.0);
                // 0-1 -> 0-128
                result += uLightColor *  vec3(shininess) * pow(intSpec, shininess * 128.0);
            }     
        }
    }

   
    oFragColor = vec4(result, 1.0);
}