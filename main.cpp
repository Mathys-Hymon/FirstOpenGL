#include<filesystem>
namespace fs = std::filesystem;

#include <stb/stb_image.h>
#include"Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"


const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};



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
	GLFWwindow* window = glfwCreateWindow(width, height,"first OpenGL", NULL, NULL);

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
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Load texture

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/FistOpenGL/Resources/";

	Texture theBlock((parentDir + texPath + "theBlock.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	theBlock.texUnit(shaderProgram, "tex0", 0);


	glEnable(GL_DEPTH_TEST); // Enable depth buffer

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));  // Create the camera
	glfwSetWindowUserPointer(window, &camera); // Link the camera to the window
	glfwSetScrollCallback(window, Camera::scroll_callback);  // set the scroll event to camera

	while (!glfwWindowShouldClose(window)) // Main While loop
	{
		glClearColor(0.07f, 0.13f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the background color and depth
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); // Set the metrix in the cam

		theBlock.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Manage all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	theBlock.Delete();
	shaderProgram.Delete();

	// Destroy the window when closed
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}