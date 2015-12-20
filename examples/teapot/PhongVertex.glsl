#version 400

uniform mat4 pkzo_ProjectionMatrix;
uniform mat4 pkzo_ViewMatrix;
uniform mat4 pkzo_ModelMatrix;

in vec3 pkzo_Vertex;
in vec3 pkzo_Normal;
in vec2 pkzo_TexCoord;
in vec3 pkzo_Tangent;

out vec3 vNormal;

void main()
{	
    mat3 normalMatrix = mat3(pkzo_ViewMatrix);
    vNormal = normalMatrix * pkzo_Normal;
    
    gl_Position = pkzo_ProjectionMatrix * pkzo_ViewMatrix * pkzo_ModelMatrix * vec4(pkzo_Vertex, 1.0);
}
