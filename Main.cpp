#include<iostream>
#include<glad/glad.h>//Primero se incluye glad.h para cargar las funciones de OpenGL antes de incluir GLFW, ya que GLFW depende de OpenGL para funcionar correctamente!!!!
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

// Funcion callback se llama cada vez que redimensiona la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // Ajusta el viewport a las nuevas dimensiones de la ventana
}

int main()
{
	glfwInit(); //Inicializa glfw para usas sus funciones
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Configura la version mayor de OpenGL como la 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Configura la version menor de OpenGL como la 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Configura el perfil de OpenGL como el core profile (no incluye funciones obsoletas) Si se usara compatibility profile se podrían usar dichas funciones obsoletas
	
	//triangulo equilatero con centro en el origen
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3))/3, 0.0f, // Abajo izquierda
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Abajo derecha
		 0.0f,  0.5f * float(sqrt(3)) *2 / 3, 0.0f  // Arriba
	};

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Crea un shader de tipo vértice y devuelve su ID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Asocia el código fuente del shader al shader creado
	glCompileShader(vertexShader); //Compila el shader de vértice

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Crea un shader de tipo fragmento y devuelve su ID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Asocia el código fuente del shader al shader creado
	glCompileShader(fragmentShader); //Compila el shader de fragmento

	GLuint shaderProgram = glCreateProgram(); //Crea un programa de shader y devuelve su ID	
	glAttachShader(shaderProgram, vertexShader); //Adjunta el shader de vértice al programa
	glAttachShader(shaderProgram, fragmentShader); //Adjunta el shader de fragmento al programa
	glLinkProgram(shaderProgram); //Enlaza el programa de shader

	glDeleteShader(vertexShader); //Elimina el shader de vértice ya que no es necesario después de enlazar el programa
	glDeleteShader(fragmentShader); //Elimina el shader de fragmento ya que no es necesario después de enlazar el programa


	GLuint VAO, VBO; //Declara variables para el Vertex Buffer Object (VBO) y el Vertex Array Object (VAO)

	glGenVertexArrays(1, &VAO); //Genera un array de vértices y almacena su ID en VAO. Se genera SIEMPRE antes que el VBO
	glGenBuffers(1, &VBO); //Genera un buffer y almacena su ID en VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Enlaza el buffer como un buffer de array

	glBindVertexArray(VAO); //Enlaza el VAO para almacenar la configuración de los atributos de vértice

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Enlaza el buffer de vértices para configurar los atributos de vértice
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copia los datos de los vértices al buffer

	//Vertex array object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Configura el atributo de vértice para la posición (location = 0 en el shader)
	glEnableVertexAttribArray(0); //Habilita el atributo de vértice para la posición

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Desenlaza el buffer de vértices
	glBindVertexArray(0); //Desenlaza el VAO

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); //Usa el programa de shader para renderizar
		glBindVertexArray(VAO); //Enlaza el VAO para usar la configuración de los atributos de vértice
		glDrawArrays(GL_TRIANGLES, 0, 3); //Dibuja el triángulo usando los vértices definidos en el VBO

		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO); //Elimina el VAO para liberar recursos
	glDeleteBuffers(1, &VBO); //Elimina el VBO para liberar recursos
	glDeleteProgram(shaderProgram); //Elimina el programa de shader para liberar recursos


	glfwDestroyWindow(window); //Destruye la ventana creada para liberar recursos
	glfwTerminate();
	return 0;
}