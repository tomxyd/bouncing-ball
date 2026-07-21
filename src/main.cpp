#include "Window.h"
#include "Texture.h"
#include "Sprite.h"
#include "CircleShape.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class object
{
private:
    const float gravity = 10.f;
    float m_radius = 2.f;
    std::size_t m_points = 6;
    CircleShape circle{m_radius, m_points};
    glm::vec2 speed;
    glm::vec2 pos{ 250.f, 50.f };
public:
    void initialize()
    {
        circle.set_position(pos);
    }
    void update()
    {
        circle.set_position({ circle.get_position().x, circle.get_position().y + gravity });
    }
    CircleShape& get_shape()
    {
        return circle;
    }
};


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

    const char* glsl_version = "#version 330";
    bool show_demo_window = true;
    bool draw_shape = false;

    Window window(glm::vec2{ 1280, 720 }, "My Window");

    window.set_frame_rate_limit(60);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls


    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.get_window(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    //CircleShape circle(5.f, 24);

    object shape1;

    shape1.initialize();

    shape1.get_shape().set_scale({ 10.f, 10.f });

    //circle.set_scale({ 10.f, 10.f });
 
    while (window.is_open())
    {
        processInput(window.get_window());
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Shape Tool");
            ImGui::Text("Shape Data");
            ImGui::Checkbox("Draw Circle", &draw_shape);
            ImGui::End();
        }

        ImGui::Render();


        window.clear();

        //circle.set_color(Color::Blue);

        if (draw_shape)
        {
            window.draw(shape1.get_shape());
            shape1.update();

        }



        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.display();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

