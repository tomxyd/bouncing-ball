#ifndef WINDOW_H
#define WINDOW_H

#include "helper_library.h"
#include "RenderTarget.h"
#include <OpenGL.h>
#include <Glm.h>

class Window : public RenderTarget
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
	/*
	* @brief clears the window context with default color
	*/
	void clear() const;
	/*
	* @brief Returns an instance of the window created.
	*/
	GLFWwindow* get_window() const
	{
		return m_window;
	}
private:
	void initialize_loaders();
private:
	GLFWwindow* m_window = NULL;
	glm::vec2 m_size;

};


#endif