#include "Shape.h"


Shape::~Shape()
{
    //glDeleteVertexArrays(1, &vertex_array);
    //glDeleteBuffers(1, &vertex_buffer);
    //glDeleteBuffers(1, &element_buffer);

}

glm::vec2 Shape::get_local_bound() const
{
    //TO DO: WRONG CALCULATION
    return { get_position().x + 1.0f, get_position().y + 1.0f };
}

void Shape::set_color(glm::vec3 color)
{
    this->color = color;
}

//Shape::Shape(const float& radius)
//{
//    set_position(glm::vec2(640.f, 360.f));
//
//    load_shader();
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//// ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // colors           // texture coords
//         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//    };
//
//    int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//    };
//
//    //glGenVertexArrays(1, &vertex_array);
//    //glGenBuffers(1, &vertex_buffer);
//    //glGenBuffers(1, &element_buffer);
//
//    //glBindVertexArray(vertex_array);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    //// position attribute
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0);
//    //// color attribute
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//    //// texture coord attribute
//    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    //glEnableVertexAttribArray(2);
//}

void Shape::update()
{
    const std::size_t count = get_point_count();
    if (count < 3)
        m_vertices.clear();

    m_vertices.resize(count + 2); // for center and repeated first point

    for (std::size_t i = 0; i < count; ++i)
        m_vertices[i + 1].position = get_point(i);
    m_vertices[count + 1].position = m_vertices[1].position; // the last position becomes the first index position

    m_vertices[0] = m_vertices[1];


}

void Shape::draw(RenderTarget& target, RenderState state) const
{
    state.m_texture = m_texture;

    //pre-transform 

    target.draw(m_vertices, state);
}

void Shape::set_shader(const Shader& shader)
{
    m_shader = &shader;
}