#include "Window.h"

Window::Window() 
{
    initialize_loaders();
}

Window::~Window()
{
    delete window;
}

Window::Window(glm::vec2& size, const char* title)
{
    Window();

    this->window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
    if (this->window == NULL)
    {
        glfwTerminate();
        Tomxy::error("failed to create window");
    }
    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    //this needs to be called after creating a window
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Tomxy::error("failed to load glad");
    }
}

bool Window::is_open() const
{
    if (glfwWindowShouldClose(this->window))
        return false;
    else
        return true;
}

void Window::display() const
{
    glfwSwapBuffers(window);

}

void Window::initialize_loaders()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


}