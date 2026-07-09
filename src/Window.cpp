#include "Window.h"

Window::Window() 
{
    initialize_loaders();
}

Window::~Window() = default;

Window::Window(glm::vec2& size, const char* title)
{
    Window();
    this->m_size = size;
    this->m_window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
    if (this->m_window == NULL)
    {
        glfwTerminate();
        Tomxy::error("failed to create window");
    }
    glfwMakeContextCurrent(m_window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

//void Window::draw(RenderTarget& target)
//{
//    glm::mat4 ortho = glm::ortho(0.0f, size.x, size.y, 0.0f, -1.f, 1.f);
//    
//}