#version 400

#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

uniform vec3      uMaterialAlbedo;
uniform float     uMaterialRoughness;
uniform bool      uMaterialHasTexture;
uniform sampler2D uMaterialTexture;

uniform int       uLightType;
uniform vec3      uLightDirection;
uniform vec3      uLightPosition;
uniform float     uLightRange;
uniform float     uLightCutoff;
uniform vec3      uLightColor;

out vec4 oFragColor;

void main()
{
    vec3 result = vec3(0);

    result += uMaterialAlbedo;
    
    oFragColor = vec4(result, 1.0);
}
