#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "Shader.h"
// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.

class ResourceManager
{

public:
	~ResourceManager()
	{
		clear();
	}
	static std::map<std::string, Shader> Shaders;

	static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

	static Shader& GetShader(std::string name);

	static void clear();
private:
	ResourceManager() {}

	static Shader& LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};
#endif
