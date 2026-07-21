#include "Window.h"

Window::Window() 
{
    initialize_loaders();
}

Window::~Window() = default;

Window::Window(glm::vec2& size, const char* title)
{
    initialize_loaders();
    this->m_size = size;
    set_viewport(size);
    this->m_window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
    if (this->m_window == NULL)
    {
        glfwTerminate();
        Tomxy::error("failed to create window");
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSwapInterval(m_fps);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    //this needs to be called after creating a window
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Tomxy::error("failed to load glad");
    }

    //Load shader
    ResourceManager::LoadShader(RESOURCES_PATH "sprite_vertex.glsl", RESOURCES_PATH "sprite_fragment.glsl", "shader1");

}



bool Window::is_open() const
{
    if (glfwWindowShouldClose(this->m_window))
        return false;
    else
        return true;
}

void Window::display() const
{
    glfwSwapBuffers(m_window);
    if (m_frame_rate_changed == true)
    {
        glfwSwapInterval(m_fps);
        m_frame_rate_changed = false;
    }
}

void Window::initialize_loaders()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::clear() const
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::set_frame_rate_limit(const unsigned int& fps)
{
    m_frame_rate_changed = true;
    switch (fps)
    {
    case 60:
        m_fps = 6;
        break;
    case 90:
        m_fps = 4;
        break;
    default: // no limit
        m_fps = 0;
        break;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
