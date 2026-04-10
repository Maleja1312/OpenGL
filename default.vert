#version 330 core
layout (location = 0) in vec3 aPos; //Entrada de posición del vértice (location = 0 en el shader)
layout (location = 1) in vec3 aColor; //Entrada de color del vértice (location = 1 en el shader)
layout (location = 2) in vec2 aTexCoord; //Entrada de coordenadas de textura del vértice (location = 2 en el shader)

out vec3 ourColor; //Salida del color del vértice para pasar al shader de fragmento

out vec2 TexCoord; //Salida de las coordenadas de textura para pasar al shader de fragmento

uniform mat4 transform; //Uniforme para la matriz de transformación

void main()
{
   gl_Position = transform * vec4(aPos, 1.0f); //Convierte la posición del vértice de vec3 a vec4 (x, y, z, w) para que OpenGL pueda procesarla. w se establece en 1.0 para mantener la posición original sin perspectiva
   ourColor = aColor; //Pasa el color del vértice a la variable de salida ourColor para que el shader de fragmento pueda usarlo para determinar el color final del pixel
   TexCoord = vec2(aTexCoord.x, aTexCoord.y); //Pasa las coordenadas de textura del vértice a la variable de salida TexCoord para que el shader de fragmento pueda usarlo para mapear la textura correctamente
}