#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);


	int width;   // size of the viewport
	int height;  // size of the viewport

	float speed = 0.1f;
	float minSpeed = 0.01f;
	float maxSpeed = 10.0f;
	float sensitivity = 100.0f;
	bool firstClick = true;

	Camera(int width, int height, glm::vec3 position);

	// Change the speed of the camera depanding of the scroll
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); 
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	// handle camera input
	void Inputs(GLFWwindow* window); 
};