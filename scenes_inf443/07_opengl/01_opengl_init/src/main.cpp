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
#include <cmath>



GLFWwindow* create_window_using_glfw();
void glfw_error_callback(int error, const char* description);

int main(int, char* argv[])
{
	// Debug message (name of the program)
	std::cout << "Run " << argv[0] << std::endl;


	// Create the window using GLFW
	GLFWwindow* window = create_window_using_glfw();


	// Display loop
	std::cout << "\nStart display loop ..." << std::endl;
	while (!glfwWindowShouldClose(window)) // loop as long as the window is not closed
	{
		// Set here the color used to clear the window at each frame
		glClearColor(0.8f, 0.6f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

		
	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


GLFWwindow* create_window_using_glfw()
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


	// Create a window taking 1/4 of your window size
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int const width = mode->width / 4;
	int const height = mode->height / 4;
	
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