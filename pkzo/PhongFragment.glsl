#version 400

uniform vec3      uMaterialColor;
uniform bool      uMaterialHasTexture;
uniform sampler2D uMaterialTexture;

#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

uniform int       uLightType;
uniform vec3      uLightDirection; // transform by view / normal matrix?
uniform vec3      uLightPosition;  // transform by view matrix
uniform float     uLightAngle;
uniform vec3      uLightColor;

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 gl_FragColor;

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
		float atten     = 1.0f;
		vec3  direction = uLightDirection;
		vec3  normal    = normalize(vNormal);

		float nDotL = dot(direction, normal);
		if (nDotL > 0.00001)
		{
			result += nDotL * materialColor * uLightColor * atten;       
		}
	}

    gl_FragColor = vec4(result, 1.0);
}
