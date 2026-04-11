#include<iostream>
#include<glad/glad.h>//Primero se incluye glad.h para cargar las funciones de OpenGL antes de incluir GLFW, ya que GLFW depende de OpenGL para funcionar correctamente!!!!
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <glm/glm.hpp> //Incluye la biblioteca GLM para matemáticas
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h" //Incluye la clase Shader
#include"VAO.h"//Incluye la clase VAO
#include"VBO.h"//Incluye la clase VBO
#include"EBO.h"//Incluye la clase EBO


// Funcion callback se llama cada vez que redimensiona la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // Ajusta el viewport a las nuevas dimensiones de la ventana
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



int main()
{
	glfwInit(); //Inicializa glfw para usas sus funciones
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Configura la version mayor de OpenGL como la 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Configura la version menor de OpenGL como la 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Configura el perfil de OpenGL como el core profile (no incluye funciones obsoletas) Si se usara compatibility profile se podrían usar dichas funciones obsoletas
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "TutorialOpenGL", NULL, NULL); //El objeto tipo GLFWwindow llamado window se inicializa con la función glfwCreateWindow (ancho, alto, titulo, monitor, share)
	//Se crea una ventana de 800x600 pc con título "TutorialOpenGL"
	//Monitor y share se establecen en NULL, es decir no se especifica un monitor para pantalla completa ni se comparte recursos con otra ventana
	if (window == NULL) //Si hay una falla al crear la ventana, muestra un mensaje de error y se termina glfw para liberar recursos y se retorna -1 para indicar el error
	{
		std::cout << "Failed to create GLFW window" << std::endl; //Mensaje
		glfwTerminate(); //Termina glfw
		return -1;
	}

	glfwMakeContextCurrent(window); // Hace que la ventana sea el contexto actual

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // Inicializa GLAD
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 800, 800); // Ajusta viewport inicial
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Registra la función callback

	//Vertices de triangulo equilatero con centro en el origen
	float vertices[] =
	{ 	//Posicion            //Color				   //Texcoords 
		-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	//cara trasera
		 0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	//cara frontal
		 0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	//cara izquierda
		-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	//cara derecha
		 0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	//cara inferior
		 0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	//cara superior
		 0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f
	};


	GLuint indices[] = {
		0, 2, 1 , //Triangulo superior
		0, 3, 2	  //Triangulo inferior
	};

	//Posiciones de 10 cubos en el espacio 3D
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader shaderProgram("default.vert", "default.frag"); //Crea un objeto de la clase Shader llamado shaderProgram, que compila y enlaza los shaders "default.vert" y "default.frag"
	
	VAO VAO1; //Crea un objeto de la clase VAO llamado VAO1
	VAO1.Bind(); //Enlaza el VAO para usarlo

	VBO VBO1(vertices, sizeof(vertices)); //Crea un objeto de la clase VBO llamado VBO1, que carga los datos de vértice definidos en el arreglo vertices
	EBO EBO1(indices, sizeof(indices)); //Crea un objeto de la clase EBO llamado EBO1, que carga los datos de índice definidos en el arreglo indices
	
    shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado

    // Configurar atributos manualmente: posición (location = 0), color (location = 1) y texcoord (location = 2)
    // Cada vértice tiene 8 floats: 3 posición, 3 color, 2 texcoords
    VBO1.Bind();
    GLsizei stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));//
    glEnableVertexAttribArray(2);
    // No desenlazamos el EBO aquí: debe permanecer ligado al VAO para glDrawElements
    VAO1.Unbind(); //Desenlaza el VAO para evitar modificaciones accidentales
    VBO1.Unbind(); //Desenlaza el VBO

	//Texturas

    int widthImg, heightImg, numColCh;
    // Flip vertically so texture coords match OpenGL convention (optional depending on image)
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("descarga.jpg", &widthImg, &heightImg, &numColCh, 0); //Carga la imagen "descarga.jpg"

	GLuint texture;
	glGenTextures(1, &texture); //Genera un ID para la textura
	glActiveTexture(GL_TEXTURE0); //Activa la unidad de textura 0
	glBindTexture(GL_TEXTURE_2D, texture); //Enlaza la textura como una textura 2D

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Configura el modo de envoltura en S (horizontal) como repetición
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Configura el modo de envoltura en T (vertical) como repetición

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Configura el modo de filtrado para reducción (minificación) como nearest (vecino más cercano). S significa la coordenada horizontal de la textura (x)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Configura el modo de filtrado para ampliación (magnificación) como nearest (vecino más cercano). T significa la coordenada vertical de la textura (y)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes); //Carga la imagen en la textura usando glTexImage2D. Especifica el formato de la imagen (RGB) y el tipo de datos (unsigned byte)
	glGenerateMipmap(GL_TEXTURE_2D); //Genera mipmaps para la textura, lo que mejora la calidad visual al reducir la textura a tamaños más pequeños


	stbi_image_free(bytes); //Libera la memoria de la imagen cargada
	glBindTexture(GL_TEXTURE_2D, 0); //Desenlaza la textura

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0"); //Obtiene la ubicación del uniform "tex0" en el shader program
    shaderProgram.Activate(); //Activa el shader program para usarlo
    glUniform1i(tex0Uni, 0); //Asigna la unidad de textura 0 al sampler (usar glUniform1i)

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		processInput(window);
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture); //Enlaza la textura como una textura 2D

		VAO1.Bind(); //Enlaza el VAO para usarlo en el renderizado
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Dibuja el triángulo usando los vértices definidos en el VBO 
		glDrawArrays(GL_TRIANGLES, 0, 36); //Dibuja el cubo usando los vértices definidos en el VBO. El segundo parámetro es el índice de inicio (0) y el tercero es el número de vértices a dibujar (36 para un cubo con 12 triángulos)



		shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado

		// Activar shader y subir view/projection cada frame
		shaderProgram.Activate();
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind VAO y textura (ya haces glBindTexture antes)
		VAO1.Bind();
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = (20.0f * (i+1)) / 2.7 ;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		VAO1.Unbind();
		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Para liberar recursos, se eliminan los objetos de OpenGL creados (VAO, VBO, shader program), se destruye la ventana creada y termina GLFW para liberar recursos
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}