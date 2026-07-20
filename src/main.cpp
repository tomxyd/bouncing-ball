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
    Window window(glm::vec2{ 1280, 720 }, "My Window");

    CircleShape circle(10.f, 12);

    float speed = 20.f;

    std::cout << circle.get_geometric_centre().x << ", " << circle.get_geometric_centre().y;

    circle.set_scale({ 10.f, 10.f });

    circle.set_origin(circle.get_geometric_centre());

     
    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        window.clear();

        circle.set_color(Color::Red);

        circle.set_position({ 250.f, 250.f });

        circle.set_rotation(45);

        window.draw(circle);

        window.display();
    }
    glfwTerminate();
}
void test_vertex_array()
{
    Window window(glm::vec2{ 1280, 720 }, "My Window");

    VertexArray lines(PrimitiveType::LineStrip, 4);
    lines[0].position = glm::vec2(10.0f, 0);
    lines[1].position = glm::vec2(20.0f, 0);
    lines[2].position = glm::vec2(30.f, 5.f);
    lines[3].position = glm::vec2(40.f, 2.f);

    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        window.clear();

        window.draw(lines);

        window.display();
    }
    glfwTerminate();
}


int main()
{
    //test_sprite();
    //test_vertex_array();
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
