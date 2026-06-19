#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "helper_library.h"
#include "SphereRenderer.h"
#include "object_renderer.h"
#include "ResourceManager.h"
#include "camera.h"
#include "Utils.h"
#include "Shader.h"

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


float aspectRatio;
//===== camera ========//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float mouseX;
float mouseY;

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    mouseX = static_cast<float>(xposIn);
    mouseY = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void initialize_loaders()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* create_window() 
{
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Window", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        Tomxy::error("failed to create window");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    return window;
}

void load_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Tomxy::error("failed to load glad");
    }
}

GLFWwindow* window = NULL;
ObjectRenderer* object_renderer = NULL;
SphereRenderer* sphere1 = NULL;

int main()
{

    initialize_loaders();
    window = create_window();
    load_glad();

    ResourceManager::LoadShader(RESOURCES_PATH "vertex.glsl", RESOURCES_PATH "fragment.glsl", "shader1");

    object_renderer = new ObjectRenderer(ResourceManager::GetShader("shader1"), RESOURCES_PATH "Mesh.obj");
    sphere1 = new SphereRenderer(ResourceManager::GetShader("shader1"));

    //object_renderer->initialize_render_data();
    //sphere1->initialize_render_data();

    int width = SCR_WIDTH;
    int height = SCR_HEIGHT;
    aspectRatio = (float)width / (float)height;

    //float ndcX = (2.0f * mouseX) / width - 1.0f;
    //float ndcY = 1.0f - (2.0f * mouseY) / height;

    while (!glfwWindowShouldClose(window))
    {

        //std::cout << ndcX << std::endl;
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        //display(glfwGetTime());
        glfwGetFramebufferSize(window, &width, &height);


        glClear(GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_CULL_FACE);

        object_renderer->draw_mesh(aspectRatio, camera);
        sphere1->draw_mesh(aspectRatio, glm::vec3(-3.0f, 2.0f , -8.0f), camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    ResourceManager::clear();
    delete object_renderer;
    delete sphere1;
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
