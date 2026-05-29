#include"Model.h"

// Funcion callback se llama cada vez que redimensiona la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // Ajusta el viewport a las nuevas dimensiones de la ventana
}
// Procesa la entrada del teclado
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Llama a la función callback

	Shader shaderProgram("default.vert", "default.frag"); //Crea un objeto de la clase Shader llamado shaderProgram, que compila y enlaza los shaders "default.vert" y "default.frag"

	glm::vec3 lightColor = glm::vec3(1.0f); //Define el color de la luz como blanco (RGBA)
	glm::vec3 lightPos = glm::vec3(0.0f, 30.0f, 50.0f); //Define la posición de la luz en el espacio 3D (mover hacia la escena)
	glm::mat4 lightModel = glm::mat4(1.0f); //Crea una matriz de modelo para la luz, inicializada como la matriz identidad (sin transformaciones)
	lightModel = glm::translate(lightModel, lightPos); //Aplica una traslación a la matriz de modelo para colocar la luz en la posición definida por lightPos

	shaderProgram.Activate(); //Activa el shader program para usarlo en el renderizado
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z); //Sube el color de la luz al shader
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z); //Sube la posición de la luz al shader de objetos



	//Crea objeto Camera para manejar la vista y proyección
    Camera camera(800, 800, glm::vec3(9.0f, 3.0f, -100.0f));

	camera.startBezierPath(
		glm::vec3(-50.0f, 5.0f, -150.0f),
		glm::vec3(-30.0f, 25.0f, -50.0f),
		glm::vec3(30.0f, 25.0f, -50.0f),
		glm::vec3(5.0f, 5.0f, -5.0f),
		15.0f
	);



	Model model("models/map/scene.gltf");

	// Variables para calcular deltaTime (tiempo entre frames)
	double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = 0.0f;

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		currentTime = glfwGetTime();
		deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		processInput(window);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static int currentModel = 3;
		std::map<int, const char*> models = {
			{GLFW_KEY_1, "models/bunny/scene.gltf"},
			{GLFW_KEY_2, "models/grindstone/scene.gltf"},
			{GLFW_KEY_3, "models/map/scene.gltf"},
			{GLFW_KEY_4, "models/scroll/scene.gltf"},
			{GLFW_KEY_5, "models/sword/scene.gltf"}
		};//Mapa que asocia teclas (1-5) con rutas de modelos GLTF para cargar diferentes modelos al presionar las teclas correspondientes

		for (auto& [tecla, modelPath] : models) {//Itera sobre el mapa de modelos, verificando si alguna de las teclas asociadas a los modelos está siendo presionada
			if (glfwGetKey(window, tecla) == GLFW_PRESS && currentModel != tecla) {
				model.reload(modelPath); 
				currentModel = tecla;//Actualiza la variable currentModel con la tecla del modelo recién cargado. Evita cargar un modelo ya cargado
			}
		}

		if (!camera.isFollowingPath())
		{
			camera.Inputs(window); // Solo permitir entrada si no sigue ruta
		}

		camera.updateBezierPath(deltaTime); // Actualizar posición en la curva
		camera.updateMatrix(70.0f, 0.1f, 200.0f);
		model.Draw(shaderProgram, camera); //Llama al método Draw del objeto model para renderizar el modelo 3D usando el shader program y la cámara configurada

		// Intercambia buffers y procesa eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}