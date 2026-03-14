#include<iostream>
#include<glad/glad.h>//Primero se incluye glad.h para cargar las funciones de OpenGL antes de incluir GLFW, ya que GLFW depende de OpenGL para funcionar correctamente!!!!
#include<GLFW/glfw3.h>

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

	glViewport(0, 0, 800, 800); // Ajusta viewport inicial
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Registra la función callback

	//Vertices de triangulo equilatero con centro en el origen
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 1.0f, 0.0f, 0.0f, //Abajo izquierda
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 1.0f, 0.0f, //Abajo derecha
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, 0.0f, 1.0f, //Arriba
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 1.0f, 0.0f, 0.0f, //Interior izquierda
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 1.0f, 0.0f, //Interior derecha
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f //Interior abajo
	};

	GLuint indices[] = {
		0, 3, 5, //Triangulo inferior izquierdo
		3, 2, 4, //Triangulo inferior derecho
		5, 4, 1 //Triangulo superior
	};

	Shader shaderProgram("default.vert", "default.frag"); //Crea un objeto de la clase Shader llamado shaderProgram, que compila y enlaza los shaders "default.vert" y "default.frag"
	
	VAO VAO1; //Crea un objeto de la clase VAO llamado VAO1
	VAO1.Bind(); //Enlaza el VAO para usarlo

	VBO VBO1(vertices, sizeof(vertices)); //Crea un objeto de la clase VBO llamado VBO1, que carga los datos de vértice definidos en el arreglo vertices
	EBO EBO1(indices, sizeof(indices)); //Crea un objeto de la clase EBO llamado EBO1, que carga los datos de índice definidos en el arreglo indices
	
    shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado

    // Configurar atributos manualmente: posición (location = 0) y color (location = 1)
    // Cada vértice tiene 6 floats: 3 para posición, 3 para color
    VBO1.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // No desenlazamos el EBO aquí: debe permanecer ligado al VAO para glDrawElements
    VAO1.Unbind(); //Desenlaza el VAO para evitar modificaciones accidentales
    VBO1.Unbind(); //Desenlaza el VBO

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		processInput(window);
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		VAO1.Bind(); //Enlaza el VAO para usarlo en el renderizado
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //Dibuja el triángulo usando los vértices definidos en el VBO 

		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Para liberar recursos, se eliminan los objetos de OpenGL creados (VAO, VBO, shader program), se destruye la ventana creada y termina GLFW para liberar recursos
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}