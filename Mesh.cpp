#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures){
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	// Configura los atributos de vértice
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position)); //Posición
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color)); //Color
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)); //Coordenadas de textura
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal)); //Normales
	
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if(type == "diffuse")
			num = std::to_string(numDiffuse++);
		else if(type == "specular")
			num = std::to_string(numSpecular++);
		
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	if (indices.size() > 0)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}