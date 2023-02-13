// OpenGL Loader - GLAD should be included before GLFW
// GLAD: https://github.com/Dav1dde/glad
// GLAD files generated from https://glad.dav1d.de/
#include "../third_party/src/glad/include/glad/glad.hpp"

// Include GLFW
#include <GLFW/glfw3.h>

// Update GLFW variables for some system
#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#define GLFW_FALSE 0
#endif

#include <iostream> 
#include <vector>
#include <cmath>

#include "helper_opengl.hpp"



GLFWwindow* create_window_using_glfw(int width, int height);
void glfw_error_callback(int error, const char* description);

int main(int, char* argv[])
{
	// Debug message (name of the program)
	std::cout << "Run " << argv[0] << std::endl;


	// Create the window using GLFW
	GLFWwindow* window = create_window_using_glfw(600, 600);

	// ************************************************* //
	//             1 - Setup/Load the shaders            //
	// ************************************************* //
	GLuint shader = opengl_load_shader("shaders/triangle.vert.glsl", "shaders/triangle.frag.glsl");

	// ************************************************* //
	//           2 - Prepare and send data to GPU        //
	// ************************************************* //

	std::cout << "*** Setup Data ***" << std::endl;

	// 2.1 Setup contiguous array of floating point value
	// ******************************************* //
	//     Here the coordinates of the vertices position
	std::vector<GLfloat> const position = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// 2.2 Create VBO - Send data to GPU
	// ******************************************* //

	GLuint vbo = 0;
	// Create an empty VBO identifiant
	glGenBuffers(1, &vbo);
	// Activate the VBO designated by the variable "vbo"
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Send data to GPU: Fill the currently designated VBO with the buffer of data passed as parameter
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(GLfloat), &position[0], GL_STATIC_DRAW);
	// Good practice to set the current VBO to 0 (=disable VBO) after its use
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// 2.3 Create VAO - Relation between VBO organization and input variables of shaders
	// ******************************************* //
	// In this case, we have only one VBO containing triplets of floats, and used as the "layout 0" in the shader
	GLuint vao = 0;
	// Create an empty VAO identifiant
	glGenVertexArrays(1, &vao);
	// Activate the VAO designated by the variable "vao"
	glBindVertexArray(vao);
	// Indicate the VBO to parameterize
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Activate the use of the variable at index layout=0 in the shader
	glEnableVertexAttribArray(0);
	// Define the memory model of the current VBO: here contiguous triplet of floating values (x y z) at index layout=0 in the shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	// As a good practice, disable VBO and VAO after their use
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	// ******************************** //
	// Display loop
	// ******************************** //

	std::cout << "\nStart display loop ..." << std::endl;
	int counter = 0;
	while (!glfwWindowShouldClose(window)) // loop as long as the window is not closed
	{
		// Initialize the frame
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Get a "time-like" value that is incremented at each new frame.
		//  (assume a program running around 60fps for t to be similar to a time expressed in seconds)
		float const t = counter / 60.0f;
		counter++;
		// Note: An actual time can be retrieved using glfwGetTime()

		// Create an array storing a translation
		float tr[3] = {0.3f*std::sin(t), 0.3f*std::cos(t), 0.0f};

		// Locate a uniform variable called "translation" in the shader program
		GLint uniform_translation_location = glGetUniformLocation(shader, "translation");

		if (uniform_translation_location == -1) //Error display in case "translation" is not in the shader
			std::cout << "Could not locate the variable translation in the shader" << std::endl;
		

		
		// ************************************************* //
		//           3 - Displaying Data                     //
		// ************************************************* //

		glUseProgram(shader);             // Activate shader program

		// Send the value of the C++ variable "translation" to the uniform variable in the shader
		//  (the value must be updated before calling glDrawArrays)
		glUniform3f(uniform_translation_location, tr[0], tr[1], tr[2]);


		glBindVertexArray(vao);           // Activate attributes for the drawing
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw 3 vertices
		glBindVertexArray(0);
		glUseProgram(0);




		// End of frame
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


GLFWwindow* create_window_using_glfw(int width, int height)
{
	// Set GLFW callback to catch and display error
	glfwSetErrorCallback(glfw_error_callback);

	// Initialize GLFW
	int const glfw_init_value = glfwInit();
	if (glfw_init_value != GLFW_TRUE) {
		std::string s = "\nError: Failed to Initialize GLFW.\n";
		abort();
	}

	// Set GLFW parameter before creating the window
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); // change to GLFW_OPENGL_ES_API for WebGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use only modern OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Expect OpenGL 3.3 or greater
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Required for MacOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // Allow possible debug

	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE); // Take focus when created
	glfwWindowHint(GLFW_SAMPLES, 8); // Multisampling
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // Windows is not always on top

#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE); // To avoid HiDPI issues with pixel size on Mac
#endif 


	
	// Actual creation of the window
	GLFWwindow* window = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);

	// Check that the window is created
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW Window" << std::endl;
		abort();
	}
	std::cout << "\nSuccessfully created a window of size " << width << " x " << height << std::endl;


	// Set an OpenGL context for this window
	glfwMakeContextCurrent(window);

	// Initialize GLAD to get access to OpenGL functions
	//   - while GLFW is used to create a window, 
	//      another initialization is needed to get access to the correct OpenGL version.
	//      We use the library GLAD to get the correct OpenGL functions.
	const int glad_init_value = gladLoadGL();
	if (glad_init_value == 0) {
		std::cout << "Failed to Init GLAD" << std::endl;
		abort();
	}

	// Display debug information on command line
	std::cout << "\nDebug information on OpenGL version" << std::endl;
	std::cout << "\t[VENDOR]      : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\t[RENDERDER]   : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\t[VERSION]     : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\t[GLSL VERSION]: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return window;
}

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "Received GLFW error" << std::endl;
	std::cerr << "\t Error " << " (" << error << ")" << std::endl;
	std::cerr << "\t Description - " << description << std::endl;
}