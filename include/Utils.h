#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Utils
{
public:
	static GLuint  GenerateTexture(const char* imagePath);
};

#endif UTILS_H