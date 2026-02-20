#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

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
	
	glfwMakeContextCurrent(window); //Indca al programa que se quiere usar la ventana creada y le dice a GLFW que haga a la ventana parte del contexto actual de OpenGL

	gladLoadGL();//Carga las funciones necesaruas para OpenGL
	
	glViewport(0, 0, 800, 800); //Indica a OpenGL el viewport (area de renderizado) desde la esquina inferior izquierda (0,0) hasta la esquina superior derecha (800,800) de la ventana. Esto asegura que todo lo que se renderice se ajuste al tamaño de la ventana creada
	
	//BACK BUFFER -> renderiza
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f );//Indica a OpenGL que se prepare para limpiar el color de un buffer y darle otro color (red, green, blue, alpha)
	//FRONT BUFFER -> muestra
	glClear(GL_COLOR_BUFFER_BIT); //Ejecuta el comando para el que se preparo anteriormente, especificado que se quiere aplicar en el buffer de color (GL_COLOR_BUFFER_BIT)
	glfwSwapBuffers(window); //Intercambia ambos buffers para que el color deseado se muestre. Se muestra en el front buffer lo que renderizo el back buffer

	while(!glfwWindowShouldClose(window)) //Indica a la ventana que no debe cerrarse a menos de que otra funcion se lo indique
	{
		glfwPollEvents(); //Procesa eventos como la aparicion dde la ventana, su redimensionamiento, etc. Si no se procesan, la ventana no respondera a los eventos
	}
	glfwDestroyWindow(window); //Destruye la ventana creada para liberar recursos
	glfwTerminate();
	return 0;
}