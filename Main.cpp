/* Plan (pseudocódigo, detallado):
- Detectar error: faltan comas entre grupos de 6 floats en el array 'vertices', causando errores de sintaxis.
- Arreglar: asegurar que cada vértice (6 floats: vec3 posición + vec3 color) termine con una coma en el array.
- Mantener estructura y lógica original del programa.
- No modificar el resto del código salvo añadir comas faltantes.
- Resultado: el compilador deja de reportar 'se esperaba ','' y 'error de sintaxis: constante'.
*/

#include<iostream>
#include<glad/glad.h>//Primero se incluye glad.h para cargar las funciones de OpenGL antes de incluir GLFW, ya que GLFW depende de OpenGL para funcionar correctamente!!!!
#include<GLFW/glfw3.h>
#include "shader_sources.h" //Archivo con el código fuente de los shaders

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

	//Shader de vértice: Se ejecuta una vez por vértice y convierte la posición 3D del vertice en una posicion 2D en la ventana
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Crea shader de vértice y devuelve su ID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Asocia el código fuente del shader al shader creado
	glCompileShader(vertexShader); //Compila el shader de vértice

	//shader de fragmento: se ejecuta una vez por cada fragmento/pixel generado por el rasterizador y determina el color final del pixel
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Crea shader de fragmento y devuelve su ID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Asocia el código fuente del shader al shader creado
	glCompileShader(fragmentShader); //Compila el shader de fragmento

	//Programa de shader : Objeto que contiene shaders enlazados. Versión linkeada final de todos los shaders usados que permite renderizar objetos.
	GLuint shaderProgram = glCreateProgram(); //Crea un programa de shader y devuelve su ID	
	glAttachShader(shaderProgram, vertexShader); //Adjunta el shader de vértice al programa
	glAttachShader(shaderProgram, fragmentShader); //Adjunta el shader de fragmento al programa
	glLinkProgram(shaderProgram); //Enlaza el programa de shader

	glDeleteShader(vertexShader); //Elimina shader de vértice, no es necesario después de enlazar el programa
	glDeleteShader(fragmentShader); //Elimina shader de fragmento, ''

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

	unsigned int VAO, VBO, EBO; //Declara variables para el Vertex Buffer Object (VBO) y el Vertex Array Object (VAO)
	//Vertex Buffer: Buffer de memoria en GPU que almacena informacion de vertices
	//Vertex Array Object: Objeto que almacena la configuración de atributos de vértice y el VBO asociado, para renderizar objetos de manera eficiente al enlazar el VAO en vez de configurar los atributos cada vez

	glGenVertexArrays(1, &VAO); //Genera un array de vértices y almacena su ID en VAO. Se genera SIEMPRE antes que el VBO
	glGenBuffers(1, &VBO); //Genera un buffer y almacena su ID en VBO
	glGenBuffers(1, &EBO); //Genera un buffer para los indices y almacena su ID en EBO
	
	glBindVertexArray(VAO); //Enlaza VAO para almacenar la configuración de los atributos de vértice para que cualquier configuración de vértices se guarde en VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Enlaza el buffer de vértices para configurar los atributos de vértice
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copia datos del array de vertices al buffer de vertices en la GPU (en VBO). GL_STATIC_DRAW indica que los datos no cambiarán o cambiarán muy poco

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Enlaza el buffer de índices para configurar los atributos de vértice
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Copia datos del array de índices al buffer de índices en la GPU (en EBO). GL_STATIC_DRAW indica que los datos no cambiarán o cambiarán muy poco

	//Vertex array object: Configura los atributos de vértice para que OpenGL sepa cómo interpretar los datos del buffer de vértices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Configura el atributo de vértice para la posición (location = 0 en el shader)
	//glVertexAttribPointer(location, size, type, normalized, stride, pointer)

	glEnableVertexAttribArray(0); //Habilita el atributo de vértice para la posición (le dice a OpenGL que use el atributo de vértice en location = 0 para renderizar)

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//1 configura el atributo de vértice para el color (location = 1 en el shader). 3 configura el tamaño del atributo (vec3), 6 * sizeof(float) es el stride (tamaño total de un vértice en bytes), y (void*)(3 * sizeof(float)) es el offset (desplazamiento en bytes desde el inicio del vértice hasta el atributo de color)
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProgram);//Usa el programa de shader para renderizar

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Desenlaza el buffer de vértices (VBO) para evitar modificaciones accidentales
	glBindVertexArray(0); //Desenlaza el VAO para evitar modificaciones accidentales a la configuración de los atributos de vértice
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Desenlaza el buffer de índices (EBO) para evitar modificaciones accidentales. SIEMPRE despues de desenlazar el VAO, ya que el EBO está asociado al VAO

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		processInput(window);
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO); //Enlaza el VAO para usar la configuración de los atributos de vértice
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //Dibuja el triángulo usando los vértices definidos en el VBO 

		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Para liberar recursos, se eliminan los objetos de OpenGL creados (VAO, VBO, shader program), se destruye la ventana creada y termina GLFW para liberar recursos
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}