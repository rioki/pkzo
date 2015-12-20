#version 400

uniform int  pkzo_LightType;
uniform vec3 pkzo_LightDirection;
uniform vec3 pkzo_LightColor;

uniform vec3 uColor;

in vec3 vNormal;

out vec4 gl_FragColor;

void main()
{
    vec3 result = vec3(0);

    // material
    vec3 color = uColor;
    
    vec3 normal = normalize(vNormal);
    
    vec3 direction;
    float atten;
    if (pkzo_LightType == 0) // directional light
    {
        direction = pkzo_LightDirection;   
        atten = 1.0;
    }
    
    float nDotL = dot(direction, normal);
    if (nDotL > 0.00001)
    {
        result += nDotL * color * pkzo_LightColor * atten;
    }

    gl_FragColor = vec4(result, 1.0);
}
