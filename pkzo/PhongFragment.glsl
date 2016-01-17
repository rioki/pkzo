#version 400

uniform vec3      uMaterialColor;
uniform bool      uMaterialHasTexture;
uniform sampler2D uMaterialTexture;
#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

uniform int       uLightType;
uniform vec3      uLightDirection;
uniform vec3      uLightPosition;
uniform float     uLightRange;
uniform float     uLightCutoff;
uniform vec3      uLightColor;

in  vec3 vPosition;
in  vec3 vNormal;
in  vec2 vTexCoord;

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

            //atten = dot(lightDirection, uLightDirection) < uLightCutoff;
            
            if (dot(lightDirection, uLightDirection) < uLightCutoff) 
            {
                atten = 1.0;
                discard;
            }
        }
    
        vec3  normal = normalize(vNormal);
        float nDotL  = dot(lightDirection, normal);
        if (nDotL > 0.00001)
        {
            result += nDotL * materialColor * uLightColor * atten;
        }
    }

   
    oFragColor = vec4(result, 1.0);
}

