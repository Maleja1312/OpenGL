#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"

class Texture
{
public:
	GLuint ID; //ID de la textura generada por OpenGL
	const char* type; //Tipo de textura (GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, etc.)
	GLuint unit; //Unidad de textura a la que se asignará la textura (GL_TEXTURE0, GL_TEXTURE1, etc.)

	Texture(const char* image, const char* texType, GLenum slot); //Constructor que carga la imagen y genera la textura
	
	void texUnit(Shader& shader, const char* uniform, GLuint unit); //Asigna la unidad de textura al uniform del shader
	void Bind(); //Enlaza la textura
	void Unbind(); //Desenlaza la textura
	void Delete(); //Elimina la textura para liberar recursos
};


#endif