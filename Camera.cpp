#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);//Calcula la matriz de vista usando la función glm::lookAt, que toma la posición de la cámara, el punto al que está mirando (Position + Orientation) y el vector Up para determinar la orientación de la cámara
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);//Calcula la matriz de proyección perspectiva usando la función glm::perspective, que toma el campo de visión en grados (convertido a radianes), la relación de aspecto (ancho/alto), el plano cercano y el plano lejano
	
	cameraMatrix = projection * view; //Combina las matrices de vista y proyección para obtener la matriz de cámara final
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Orientation; // Move forward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= speed * Orientation; // Move backward
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed; // Move left
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed; // Move right
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += speed * Up; // Move up
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position -= speed * Up; // Move down
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.4f; // Increase speed when left shift is pressed
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 0.1f; // Increase speed when left shift is pressed
	  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hide the cursor when left mouse button is pressed
	
		if(firstClick) // This bool variable is initially set to true
		{
			glfwSetCursorPos(window, width / 2, height / 2); // If it's the first time the mouse button is pressed, set the cursor to the center of the screen
			firstClick = false; // Set the variable to false so this block won't be executed again
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY); // Get the current mouse position

		float rotx = sensitivity * (float)(mouseY - height / 2) / height; // Calculate rotation around the x-axis based on mouse movement
		float roty = sensitivity * (float)(mouseX - width / 2) / width; // Calculate rotation around the y-axis based on mouse movement

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, Up))); // Rotate the orientation vector around the x-axis
		
		if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) || glm::angle(newOrientation, -Up) <= glm::radians(5.0f))) // Prevent the camera from flipping upside down
			Orientation = newOrientation;

		Orientation = glm::rotate(Orientation, glm::radians(-roty), Up); // Rotate the orientation vector around the y-axis
		glfwSetCursorPos(window, width / 2, height / 2); // Reset the mouse position to the center of the window
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Show the cursor when left mouse button is released
		firstClick = true; // Set the variable to true so the next time the mouse button is pressed, the cursor will be centered again
	}
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}