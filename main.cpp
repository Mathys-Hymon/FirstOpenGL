#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main \n"
"{ \n"
"     FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";  

int main()
{

	// Initialize GLFW
	glfwInit();


	// Set the GLFW Version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Define if GLFW use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(800, 800,"first OpenGL", NULL, NULL);

	if (window == NULL) // Return error if window dont create correctly
	{
		std::cout << "\n\nFailed to create GLFW Window\n\n" << std::endl;

		glfwTerminate();
		return -1;
	}

	// Set the window to the current context
	glfwMakeContextCurrent(window);

	// Load Glad for OpenGL
	gladLoadGL();

	// Set the viewport Size
	glViewport(0, 0, 800, 800);

	// Set the color of the background buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear the front buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the buffers
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) // Main While loop
	{

		// Manage all GLFW events
		glfwPollEvents();
	}

	// Destroy the window when closed
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}