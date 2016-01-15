#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

in vec3 aVertex;

out vec3 vTexCoord;

void main()
{
    mat4 r = uViewMatrix;
    r[3][0] = 0.0;
    r[3][1] = 0.0;
    r[3][2] = 0.0;
    
    vec4 vi = vec4(aVertex, 1.0);

    vec4 v = inverse(r) * inverse(uProjectionMatrix) * vi;

    vTexCoord    = v.xyz; 
    gl_Position  = vi;
}
