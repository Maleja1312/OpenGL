#include"Mesh.h"

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


class Cubo {
public:
	std::vector<float> vertices;
	std::vector<glm::vec3> posiciones;

	void setPosiciones() {
		posiciones = {
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
	}
	glm::vec3* getPosiciones()
	{
		return posiciones.data();
	}

	void setVertices()
	{
		vertices = {
			// Posicion            //Color				   //Texcoords	//Normales
			-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,	//cara trasera
			 0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	//cara frontal
			 0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,	//cara izquierda
			-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	1.0f,  0.0f,  0.0f,	//cara derecha
			 0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.847f, 0.706f, 0.902f,  0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 0.0f,	1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	0.0f, -1.0f,  0.0f,	//cara inferior
			 0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,	0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	0.0f,  1.0f,  0.0f,	//cara superior
			 0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.847f, 0.706f, 0.902f,  1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  1.000f, 0.714f, 0.757f,  0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  1.000f, 0.788f, 0.851f,  0.0f, 1.0f,	0.0f,  1.0f,  0.0f
		};
	}
	float* getVertices()
	{
		return vertices.data();
	}
};

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
	Cubo cubitos; //Crea un objeto de la clase Cubo llamado cubitos
	// Inicializar datos antes de obtener punteros a su memoria interna			
	cubitos.setVertices();
	cubitos.setPosiciones();
	float* vertices = cubitos.getVertices(); //Puntero a los vértices del cubo (ya inicializados)

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

    //Posiciones de 10 cubos en el espacio 3D (se usa el array estático más abajo)
	// Nota: no usar el puntero a cubitos.getPosiciones() para evitar duplicar datos

	GLfloat lightVertices[] =
	{	//    COORDENADAS   //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f,
	};

	GLuint lightIndices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

// Número de índices para el cubo de la luz
	GLsizei lightIndexCount = sizeof(lightIndices) / sizeof(lightIndices[0]);

	//Imagen de textura
	const char* texture1 = "descarga.jpg"; //Asigna la ruta de la imagen de textura a la variable texture

	Shader shaderProgram("default.vert", "default.frag"); //Crea un objeto de la clase Shader llamado shaderProgram, que compila y enlaza los shaders "default.vert" y "default.frag"
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex)); //Crea un vector de vértices llamado verts, que se inicializa con los datos del arreglo vertices. El tamaño del vector se calcula dividiendo el tamaño total del arreglo por el tamaño de un float (ya que cada vértice tiene múltiples componentes)
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint)); //Crea un vector de índices llamado ind, que se inicializa con los datos del arreglo indices. El tamaño del vector se calcula dividiendo el tamaño total del arreglo por el tamaño de un GLuint (ya que cada índice es un GLuint) el vector indices se define en Mesh.h
	std::vector<Texture> tex(texture1, texture1 + sizeof(texture1) / sizeof(Texture)); //Crea un vector de texturas llamado tex, que se inicializa con los datos del arreglo textures. El tamaño del vector se calcula dividiendo el tamaño total del arreglo por el tamaño de un Texture (ya que cada textura es un objeto de la clase Texture) texture corresponde a la textura cargada en el main, se define como GLuint texture y se carga con la imagen "descarga.jpg"
	Mesh floor(verts, ind, tex); //Crea un objeto de la clase Mesh llamado floor, que se inicializa con los vértices, índices y texturas definidos en los vectores verts, ind y tex respectivamente. Este objeto representa el piso de la escena

	Shader lightShader("light.vert", "light.frag"); //Crea un objeto de la clase Shader llamado lightShader, que compila y enlaza los shaders "light.vert" y "light.frag"
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex)); //Crea un vector de vértices llamado lightVerts, que se inicializa con los datos del arreglo lightVertices. El tamaño del vector se calcula dividiendo el tamaño total del arreglo por el tamaño de un float (ya que cada vértice tiene múltiples componentes)
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint)); //Crea un vector de índices llamado lightInd, que se inicializa con los datos del arreglo lightIndices. El tamaño del vector se calcula dividiendo el tamaño total del arreglo por el tamaño de un GLuint (ya que cada índice es un GLuint)
	Mesh light(lightVerts, lightInd, tex); //Crea un objeto de la clase Mesh llamado light, que se inicializa con los vértices y índices definidos en los vectores lightVerts y lightInd respectivamente, y un vector de texturas vacío. Este objeto representa la luz en la escena

	// Configuración de la luz
	glm::vec3 lightColor = glm::vec3(1.0f); //Define el color de la luz como blanco (RGBA)
    glm::vec3 lightPos= glm::vec3(0.8f, 0.9f, 0.0f); //Define la posición de la luz en el espacio 3D (mover hacia la escena)
	glm::mat4 lightModel = glm::mat4(1.0f); //Crea una matriz de modelo para la luz, inicializada como la matriz identidad (sin transformaciones)
	lightModel = glm::translate(lightModel, lightPos); //Aplica una traslación a la matriz de modelo para colocar la luz en la posición definida por lightPos

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

	glm::mat4 modelo = glm::mat4(1.0f); //Crea una matriz de modelo para los cubos, inicializada como la matriz identidad (sin transformaciones)
	modelo = glm::translate(modelo, cubePositions[0]); //Aplica una traslación a la matriz de modelo para colocar el primer cubo en la posición definida por cubePositions[0]

	lightShader.Activate(); //Activa el shader de luz para usarlo en el renderizado
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel)); //Sube la matriz de modelo de la luz al shader usando glUniformMatrix4fv. El primer parámetro es la ubicación del uniform "model", el segundo es el número de matrices a subir (1), el tercero indica si la matriz debe ser transpuesta (GL_FALSE), y el cuarto es un puntero a los datos de la matriz (obtenido con glm::value_ptr)
	glUniform3f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z); //Sube el color de la luz al shader usando glUniform4f. El primer parámetro es la ubicación del uniform "lightColor", y los siguientes son los componentes RGBA del color de la luz
	glUniform3f(glGetUniformLocation(lightShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z); //Sube la posición de la luz al shader usando glUniform3f. El primer parámetro es la ubicación del uniform "lightPos", y los siguientes son los componentes XYZ de la posición de la luz
	shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelo)); //Sube la matriz de modelo de los cubos al shader usando glUniformMatrix4fv. El primer parámetro es la ubicación del uniform "model", el segundo es el número de matrices a subir (1), el tercero indica si la matriz debe ser transpuesta (GL_FALSE), y el cuarto es un puntero a los datos de la matriz (obtenido con glm::value_ptr)
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z); //Sube el color de la luz al shader
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z); //Sube la posición de la luz al shader de objetos

	//Texturas
    int widthImg, heightImg, numColCh;

    // Flip vertically so texture coords match OpenGL convention (optional depending on image)
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("descarga.jpg", &widthImg, &heightImg, &numColCh, 0); //Carga la imagen "descarga.jpg"
	if (!bytes) {
		std::cout << "Failed to load texture 'descarga.jpg'\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	GLuint texture;//Declara una variable GLuint llamada texture para almacenar el ID de la textura generada por OpenGL
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
	// Asegurar que el shader está activo antes de asignar el uniform
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0); //Asigna la unidad de textura 0 al sampler (usar glUniform1i)

	//Crea objeto Camera para manejar la vista y proyección
    Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 3.0f)); //Crea un objeto de la clase Camera con la cámara más atrás para ver la escena


	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		processInput(window);
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture); //Enlaza la textura como una textura 2D

		camera.Inputs(window); //Llama al método Inputs del objeto camera para manejar la entrada del usuario (teclado y mouse) y actualizar la posición y orientación de la cámara en consecuencia
		camera.updateMatrix(45.0f, 0.1f, 100.0f); //Llama al método Matrix del objeto camera para configurar las matrices de vista y proyección en el shader program usando el uniform "camMatrix"
		
		floor.Draw(shaderProgram, camera); //Llama al método Draw del objeto floor para renderizar el piso usando el shader program y la cámara
		light.Draw(lightShader, camera); //Llama al método Draw del objeto light para renderizar la luz usando el shader de luz y la cámara
		
		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Para liberar recursos, se eliminan los objetos de OpenGL creados (VAO, VBO, shader program), se destruye la ventana creada y termina GLFW para liberar recursos
	
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}