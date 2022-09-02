// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#ifdef GLOW_VERTEX

uniform mat4 glow_ProjectionMatrix;
uniform mat4 glow_ViewMatrix;
uniform mat4 glow_ModelMatrix;

in vec3 glow_Vertex;
in vec2 glow_TexCoord;

out vec2 var_TexCoord;

void main()
{
    var_TexCoord = glow_TexCoord;
    gl_Position  = glow_ProjectionMatrix * glow_ViewMatrix * glow_ModelMatrix * vec4(glow_Vertex, 1.0);
}

#endif

#ifdef GLOW_FRAGMENT

uniform vec4      pkzo_Color;
uniform bool      pkzo_HasTexture;
uniform sampler2D pkzo_Texture;

in vec2 var_TexCoord;

out vec4 out_FragColor;

void main()
{
    if (pkzo_HasTexture)
    {
        out_FragColor = texture(pkzo_Texture, var_TexCoord) * pkzo_Color;
    }
    else
    {
        out_FragColor = pkzo_Color;
    }
}

#endif
