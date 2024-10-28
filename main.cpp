#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"


#include<filesystem>
namespace fs = std::filesystem;

#include "Model.h"


const unsigned int width = 800;
const unsigned int height = 800;

std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
std::string contentDir = parentDir + "/FistOpenGL/Content/";

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

	if (window == NULL)												// Return error if window dont create correctly
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


	Shader shaderProgram("default.vert", "default.frag");            // Create the default shader program

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);		 // Define the color of the light
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);										// Enable depth buffer

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));		// Create the camera

	std::string modelPath = "Models/bunny/scene.gltf";

		// Load texture
	std::cout << contentDir + modelPath << std::endl;
	Model model((contentDir + modelPath).c_str());

	glfwSetWindowUserPointer(window, &camera);						// Link the camera to the window
	glfwSetScrollCallback(window, Camera::scroll_callback);			// set the scroll event to camera


		// Set up ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	while (!glfwWindowShouldClose(window))							// Main While loop
	{
		glClearColor(0.045f, 0.054f, 0.087f, 1.0f);				    // Define the background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		    // Clear the background color and depth
		 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);					//Update the matrix

		model.Draw(shaderProgram, camera);

		ImGui::Begin("Camera Manager");
		ImGui::Text("FOV :");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Swap the back buffer with the front
		glfwSwapBuffers(window);
			// Manage all GLFW events
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	shaderProgram.Delete();

		// Destroy the window when closed
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}