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
    std::size_t m_points = 12;
    CircleShape circle{m_radius, m_points};
    glm::vec2 m_speed{};
    glm::vec2 pos{ 250.f, 50.f };
public:
    void initialize()
    {
        circle.set_position(pos);
    }
    void set_radius(float radius)
    {
        circle.set_radius(radius);
    }

    void set_segment(int count)
    {
        circle.set_point_count(count);
    }
    void set_speed(glm::vec2 speed)
    {
        m_speed = speed;
    }
    void set_color(const Color& color)
    {
        circle.set_color(color);
    }
    void set_scale(glm::vec2 factor)
    {
        circle.set_scale(factor);
    }
    void update(glm::vec2 bounds)
    {
        circle.set_position({ circle.get_position().x + m_speed.x, circle.get_position().y + m_speed.y });

        if (circle.get_global_bound().position.x + circle.get_global_bound().size.x > bounds.x  || circle.get_global_bound().position.x < 0)
        {
            m_speed.x *= -1;
        }
        else if (circle.get_global_bound().position.y + circle.get_global_bound().size.y > bounds.y || circle.get_global_bound().position.y < 0)
        {
            m_speed.y *= -1;
        }
        
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

    object shape1;
    shape1.initialize();
    shape1.set_speed(glm::vec2{ -3, 2 });
    shape1.set_scale({ 20.f, 20.f });
    shape1.set_color({ 1, 0, 1 });


    float circle_radius = 2.f;
    int circle_segment = 32;
    float c[3] = { 0.f, 1.f, 1.f };
 
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
            ImGui::SliderFloat("Radius", &circle_radius, 0.f, 50.f);
            ImGui::SliderInt("Segments", &circle_segment, 4, 60);
            ImGui::ColorEdit3("Color Circle", c);
            ImGui::End();
        }

        ImGui::Render();

        shape1.set_radius(circle_radius);
        shape1.set_segment(circle_segment);
        shape1.set_color(Color(uint8_t(c[0] * 255), uint8_t(c[1] * 255), uint8_t(c[2] * 255)));
        window.clear();


        if (draw_shape)
        {
            window.draw(shape1.get_shape());
            shape1.update(glm::vec2{ 1280, 720 });
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

