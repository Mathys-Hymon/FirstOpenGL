#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"




int main()
{

	// Initialize GLFW
	glfwInit();


	// Set the GLFW Version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Define if GLFW use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		//   COORDINATES    /       COLORS       //
		-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f, // Lower right corner
	};

	GLuint indices[] =
	{
	    0, 2, 1, // Upper triangle
		0, 3, 2, // Lower triangle
	};

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

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("Textures/theBlock.png", &widthImg, &heightImg, &numColCh, 0);

	while (!glfwWindowShouldClose(window)) // Main While loop
	{
		glClearColor(0.07f, 0.13f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Manage all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroy the window when closed
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}