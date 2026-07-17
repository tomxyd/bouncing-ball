#include "Shape.h"


Shape::~Shape()
{
    //glDeleteVertexArrays(1, &vertex_array);
    //glDeleteBuffers(1, &vertex_buffer);
    //glDeleteBuffers(1, &element_buffer);

}

glm::vec2 Shape::get_local_bound() const
{
    return glm::vec2(0.f, 0.f);
}

void Shape::set_color(glm::vec3 color)
{
    this->color = color;
}

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

    state.m_transform *= getTransform();
    state.m_texture = m_texture;
    target.draw(m_vertices, state);
}

void Shape::set_shader(const Shader& shader)
{
    m_shader = &shader;
}