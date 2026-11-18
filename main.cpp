#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "util.hpp"

using namespace std;
using namespace glm;

// Global state
GLuint shader;			        // Shader program
GLuint uniXform;		        // Matrix location in shader
GLuint vao;				        // Vertex array object
GLuint vbuf;			        // Vertex buffer
GLsizei vcount;			        // Number of vertices

// Texture data
GLuint colorTex;			    // OpenGL texture holding color data
GLuint depthTex;			    // OpenGL texture holding depth data
const GLint texWidth = 640;		// Kinect image dimensions
const GLint texHeight = 480;
vector<GLubyte> colorData;	    // Color data from kinect
vector<GLubyte> depthData;	    // Depth data from kinect
int viewmode;				    // 0 = show color, 1 = show depth

// Display configurations
const int winWidth = 1400;
const int winHeight = 1050;

// Initialization functions
void initState();
void initOpenGL();

// Callback functions
void cleanup();

int main(int argc, char** argv) {
    GLFWwindow *window = nullptr;

    if (!glfwInit()) {
        cout << "GLFW Not Initialized" << endl;
        cleanup();
        return -1;
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(winWidth, winHeight, "SandSlope", nullptr, nullptr);

    if (!window) {
        cout << "Window was't created" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        cout << "Failed to load OpenGL via glad" << endl;
        glfwTerminate();
        return -1;
    }

    // Initialize State
    try {
        initState();
        initOpenGL();
    } catch (const exception& e) {
        // Handle any errors
		cerr << "Fatal error: " << e.what() << endl;
		cleanup();
		return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Wipes black buffer so you can draw on blank slate
        glfwPollEvents();                                       // Process window-system events
        glfwSwapBuffers(window);                                // Swaps color buffers to produce updated window
    }

    cleanup();
    glfwTerminate();
	return 0;
}

void initState() {
	// Initialize global state
	shader = 0;
	uniXform = 0;
	vao = 0;
	vbuf = 0;
	vcount = 0;
	colorTex = 0;
	depthTex = 0;
	viewmode = 1;	// Draw depth
}

void initOpenGL() {
	// Set clear color and depth
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set viewport
	glViewport(0, 0, winWidth, winHeight);

	// Compile and link shader program
	vector<GLuint> shaders;
	shaders.push_back(compileShader(GL_VERTEX_SHADER, "sh_v.glsl"));
	shaders.push_back(compileShader(GL_FRAGMENT_SHADER, "sh_f.glsl"));
	shader = linkProgram(shaders);

	// Release shader sources
	for (auto s = shaders.begin(); s != shaders.end(); ++s)
		glDeleteShader(*s);
	shaders.clear();

	// Locate uniforms
	uniXform = glGetUniformLocation(shader, "xform");

	// Bind texture image unit
	glUseProgram(shader);
	GLuint texLoc = glGetUniformLocation(shader, "tex");
	glUniform1i(texLoc, 0);
	glUseProgram(0);
}

void cleanup() {
    // Release all resources
	if (shader) { glDeleteProgram(shader); shader = 0; }
	uniXform = 0;
	if (vao) { glDeleteVertexArrays(1, &vao); vao = 0; }
	if (vbuf) { glDeleteBuffers(1, &vbuf); vbuf = 0; }
	vcount = 0;
	if (colorTex) { glDeleteTextures(1, &colorTex); colorTex = 0; }
	if (depthTex) { glDeleteTextures(1, &depthTex); depthTex = 0; }
	colorData.clear();
	depthData.clear();
    return;
}

