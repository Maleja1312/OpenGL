#ifndef SHADER_SOURCES_H
#define SHADER_SOURCES_H

// Código fuente de los shaders separado en un archivo aparte
static const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(1.0, 0.84, 0.9, 0.0);"
    "}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

#endif // SHADER_SOURCES_H
