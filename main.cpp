#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

// Display configurations
const int winWidth = 1400;
const int winHeight = 1050;

// Initialization functions
void initState();

// Callback functions
void cleanup();

int main(int argc, char** argv) {
    GLFWwindow *window;

    try {
        initState();
    } catch (const exception& e) {
        // Handle any errors
		cerr << "Fatal error: " << e.what() << endl;
		cleanup();
		return -1;
    }

    if (!glfwInit()) {
        cout << "GLFW Not Initialized" << endl;
        cleanup();
        return -1;
    }

    window = glfwCreateWindow(winWidth, winHeight, "SandSlope", 0, 0);

    if (!window) {
        cout << "Window was't created" << endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();               // Update OpenGL window
        glfwSwapBuffers(window);             // Rendering OpenGL window
    }

    glfwTerminate();

	return 0;
}

void initState() {
    // Initialize Global State
    cout << "State initialized..." << endl;
    return;
}

void cleanup() {
    // Release all resources
    return;
}

