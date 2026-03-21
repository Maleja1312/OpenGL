#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex0;

void main()
{
    // Modulate texture color by vertex color
    FragColor = texture(tex0, TexCoord) * vec4(ourColor, 1.0);
}
