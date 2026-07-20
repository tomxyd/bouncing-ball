#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "Sprite.h"
#include "CircleShape.h"
#include "RenderState.h"
#include "VertexArray.h"

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void test_sprite()
{
    Window window(glm::vec2{ 1280, 720 }, "My Window");

    const Texture texture(RESOURCES_PATH "brick.png");

    Sprite sprite(texture);

    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        window.clear();

        sprite.set_position({ 200.f, 200.f });

        sprite.set_scale({ 50.f, 50.f });

        window.draw(sprite);

        window.display();
    }
    glfwTerminate();
}
void test_circle_shape()
{
    Window window(glm::vec2{ 500, 500 }, "My Window");

    CircleShape circle(5.f, 24);

    circle.set_scale({ 10.f, 10.f });
 
    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        window.clear();

        circle.set_color(Color::Blue);

        circle.set_position({ 250.f, 250.f });

        window.draw(circle);

        window.display();
    }
    glfwTerminate();
}

int main()
{
    test_circle_shape();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

