#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

// Código fuente de los shaders separado en un archivo aparte
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n" //Entrada de posición del vértice (location = 0 en el shader)
    "layout (location = 1) in vec3 aColor;\n" //Entrada de color del vértice (location = 1 en el shader)
    "out vec3 ourColor;\n" //Salida del color del vértice para pasar al shader de fragmento
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n" //Convierte la posición del vértice de vec3 a vec4 (x, y, z, w) para que OpenGL pueda procesarla. w se establece en 1.0 para mantener la posición original sin perspectiva
    "   ourColor = aColor;\n"//Pasa el color del vértice a la variable de salida ourColor para que el shader de fragmento pueda usarlo para determinar el color final del pixel
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"//Establece el color final del fragmento/pixel a partir del color pasado desde el shader de vértice
    "}\n\0";

#endif // SHADER_SOURCES_H
