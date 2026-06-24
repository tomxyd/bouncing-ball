#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "camera.h"
#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "Sprite.h"

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

int main()
{
    Window window(glm::vec2{ 1280, 720 }, "My Window");

    const Texture texture(RESOURCES_PATH "brick.png");

    Sprite sprite(texture);

    float speed = 0.06f;

    sprite.set_color({ 1.0,1.0,0.0 }); // set color to yellow

    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        window.clear();

        if (sprite.get_position().x >= 1280 || sprite.get_local_bound().y >= 720)
        {
            speed *= -1;
        }
        else
            speed = speed;

        sprite.set_position({ sprite.get_position().x, sprite.get_position().y + speed });

        sprite.set_scale({150.f, 150.f});

        window.draw(sprite);



        window.display();
    }
    glfwTerminate();
    return 0;
}

//int main()
//{
//
//    initialize_loaders();
//    window = create_window();
//    load_glad();
//
//    ResourceManager::LoadShader(RESOURCES_PATH "vertex.glsl", RESOURCES_PATH "fragment.glsl", "shader1");
//
//    object_renderer = new ObjectRenderer(ResourceManager::GetShader("shader1"), RESOURCES_PATH "Mesh.obj");
//    sphere1 = new SphereRenderer(ResourceManager::GetShader("shader1"));
//
//
//    int width = SCR_WIDTH;
//    int height = SCR_HEIGHT;
//    aspectRatio = (float)width / (float)height;
//
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//        //std::cout << ndcX << std::endl;
//        // per-frame time logic
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        processInput(window);
//        //display(glfwGetTime());
//        glfwGetFramebufferSize(window, &width, &height);
//
//
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glClearColor(0.2, 0.2, 0.2, 1.0);
//        glClear(GL_COLOR_BUFFER_BIT);
//        glEnable(GL_CULL_FACE);
//
//        object_renderer->draw_mesh(aspectRatio, camera);
//        sphere1->draw_mesh(aspectRatio, glm::vec3(-3.0f, 2.0f , -8.0f), camera);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}


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
