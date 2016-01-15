#version 400

uniform samplerCube uCubeMap;

in vec3 vTexCoord;

void main()
{
    gl_FragColor = texture(uCubeMap, vTexCoord);
}
