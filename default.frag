#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex0;

uniform vec3 lightColor; // usar vec3 para color
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // color del objeto: textura * color del vértice
    vec3 objectColor = texture(tex0, TexCoord).rgb * ourColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // dirección y normal normalizadas
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // componente difusa
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
