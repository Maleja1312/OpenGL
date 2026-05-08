#include"Model.h"

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




	Shader shaderProgram("default.vert", "default.frag"); //Crea un objeto de la clase Shader llamado shaderProgram, que compila y enlaza los shaders "default.vert" y "default.frag"

	glm::vec3 lightColor = glm::vec3(1.0f); //Define el color de la luz como blanco (RGBA)
	glm::vec3 lightPos = glm::vec3(0.0f, 30.0f, 50.0f); //Define la posición de la luz en el espacio 3D (mover hacia la escena)
	glm::mat4 lightModel = glm::mat4(1.0f); //Crea una matriz de modelo para la luz, inicializada como la matriz identidad (sin transformaciones)
	lightModel = glm::translate(lightModel, lightPos); //Aplica una traslación a la matriz de modelo para colocar la luz en la posición definida por lightPos

	shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z); //Sube el color de la luz al shader
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z); //Sube la posición de la luz al shader de objetos

	//Crea objeto Camera para manejar la vista y proyección
    Camera camera(800, 800, glm::vec3(9.0f, 15.0f, -50.0f)); //Crea un objeto de la clase Camera con la cámara más atrás para ver la escena

	Model model("models/map/scene.gltf");

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{

		processInput(window);
		// Renderizado: limpiar color del buffer cada frame
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static int currentModel = -1;//Variable estática para almacenar la tecla del modelo actualmente cargado, inicializada en -1 (ningún modelo cargado)
		std::map<int, const char*> models = {
			{GLFW_KEY_1, "models/bunny/scene.gltf"},
			{GLFW_KEY_2, "models/grindstone/scene.gltf"},
			{GLFW_KEY_3, "models/map/scene.gltf"},
			{GLFW_KEY_4, "models/scroll/scene.gltf"},
			{GLFW_KEY_5, "models/sword/scene.gltf"}
		};//Mapa que asocia teclas (1-5) con rutas de modelos GLTF para cargar diferentes modelos al presionar las teclas correspondientes

		for (auto& [tecla, modelPath] : models) {//Itera sobre el mapa de modelos, verificando si alguna de las teclas asociadas a los modelos está siendo presionada (auto& es una referencia a cada par clave-valor en el mapa)
			if (glfwGetKey(window, tecla) == GLFW_PRESS && currentModel != tecla) { //Si la tecla está siendo presionada y no es el modelo actualmente cargado, se llama al método reload del objeto model para cargar el nuevo modelo desde la ruta especificada por modelPath, y se actualiza currentModel con la tecla del modelo recién cargado
				model.reload(modelPath); 
				currentModel = tecla;//Actualiza la variable currentModel con la tecla del modelo recién cargado. Evita cargar un modelo v
			}
		}

		camera.Inputs(window); //Llama al método Inputs del objeto camera para manejar la entrada del usuario (teclado y mouse) y actualizar la posición y orientación de la cámara en consecuencia
		camera.updateMatrix(70.0f, 0.1f, 500.0f); //Llama al método Matrix del objeto camera para configurar las matrices de vista y proyección en el shader program usando el uniform "camMatrix"
		
		model.Draw(shaderProgram, camera); //Llama al método Draw del objeto model para renderizar el modelo 3D usando el shader program y la cámara configurada

		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Para liberar recursos, se eliminan los objetos de OpenGL creados (VAO, VBO, shader program), se destruye la ventana creada y termina GLFW para liberar recursos
	
	
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}