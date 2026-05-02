#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 camMatrix;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    FragPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    ourColor = aColor;
    TexCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTexCoord;
    gl_Position = camMatrix * vec4(FragPos, 1.0);
}