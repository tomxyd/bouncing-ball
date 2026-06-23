#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "helper_library.h"
#include "Sprite.h"

class Sprite; //BAD: remove circular dependency

class Window
{
public:
	//Default constructor
	Window();
	//@brief Frees resources attached to the window
	~Window();
	/*
	* @brief Constructs a new window.
	*/
	Window(glm::vec2& size, const char* title);
	/*
	* @brief Returns whether the window is open or not.
	*/
	bool is_open() const;
	/*
	* @brief Swaps buffers internally.
	*/
	void display() const;
	//
	void clear() const;
	//Draw a sprite to the window
	void draw(const Sprite& sprite);
	/*
	* @brief Returns an instance of the window created.
	*/
	GLFWwindow* get_window() const
	{
		return window;
	}
private:
	void initialize_loaders();
private:
	GLFWwindow* window = NULL;
	glm::vec2 size;

};


#endif