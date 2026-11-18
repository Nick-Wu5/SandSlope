#ifndef _COMMON_HPP
#define _COMMON_HPP

#include <glad/gl.h>
#include <string>
#include <vector>

GLuint compileShader(GLenum type, std::string filename, std::string prepend = "");
GLuint linkProgram(std::vector<GLuint> shaders);

#endif