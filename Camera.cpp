#include "Camera.h"

Camera::Camera(int Width, int Height, glm::vec3 Position)
{
	Camera::width = Width;
	Camera::height = Height;

	position = Position;
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)     // detect when mouse wheel scroll
{
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		camera->speed += static_cast<float>(yoffset) * 0.01f;                       // Change sensitivity
		camera->speed = glm::clamp(camera->speed, camera->minSpeed, camera->maxSpeed);
		std::cout << "Current speed: " << camera->speed << std::endl;
	}
	else 
	{
		camera->position += (static_cast<float>(yoffset) * 0.05f) * camera->rotation;
	}
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + rotation, upVector);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}



void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)                                      // FORWARD
	{
		position += (speed * 0.1f) * rotation;
	}
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)                                      // LEFT
	{
		position += (speed * 0.1f) * -glm::normalize(glm::cross(rotation, upVector));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)                                      // BACKWARD
	{
		position += (speed * 0.1f) * -rotation;
	}
	 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)                                      // RIGHT
	{
		position += (speed * 0.1f) * glm::normalize(glm::cross(rotation, upVector));
	}




	if (glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS)                                 // UP
	{
		position += (speed * 0.1f) * upVector;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)                            // DOWN
	{ 
		position += (speed * 0.1f) * -upVector;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)                // LOOK AROUND
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}
		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newRotation = glm::rotate(rotation, glm::radians(-rotX), glm::normalize(glm::cross(rotation, upVector)));

		if (!((glm::angle(newRotation, upVector) <= glm::radians(5.0f)) || (glm::angle(newRotation, -upVector) <= glm::radians(5.0f))))
		{
			rotation = newRotation;
		}

		rotation = glm::rotate(rotation, glm::radians(-rotY), upVector);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)                // SHOW MOUSE CURSOR
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}
