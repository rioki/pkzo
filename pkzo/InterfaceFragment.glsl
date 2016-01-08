#version 400

uniform bool      uHasTexture;
uniform sampler2D uTexture;
uniform vec4      uColor;

in vec2 vTexCoord;

out vec4 gl_FragColor;

void main()
{	    
    if (uHasTexture)
    {
        gl_FragColor = texture(uTexture, vTexCoord) * uColor;	
    }
    else
    {
        gl_FragColor = uColor;
    }
}
