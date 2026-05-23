#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

inline glm::vec3 calculateBezierPoint(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	glm::vec3 p = uuu * p0;
	p += 3.0f * uu * t * p1;
	p += 3.0f * u * tt * p2;
	p += ttt * p3;

	return p;
}

class Camera
{
public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		bool firstClick = true;

		int width;
		int height;

		float speed = 0.1f;
		float sensitivity = 100.0f;

		Camera(int width, int height, glm::vec3 position);
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window);
		void startBezierPath(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float duration);
		void updateBezierPath(float deltaTime);
		bool isFollowingPath() const { return followingPath; }

private:
	glm::vec3 bezierP0, bezierP1, bezierP2, bezierP3;
	float bezierTime = 0.0f;
	float bezierDuration = 0.0f;
	bool followingPath = false;

};

#endif CAMERA_H
