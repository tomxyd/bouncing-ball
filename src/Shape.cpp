#include "Shape.h"

FloatRect Shape::get_local_bound() const
{
    return m_bounds;
}

FloatRect Shape::get_global_bound() const
{
    return get_transform().transform_rect(get_local_bound());
}

void Shape::set_color(Color color)
{
    m_color = color;
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
    m_bounds = m_vertices.get_bounds();

}

void Shape::draw(RenderTarget& target, RenderState state) const
{

    state.m_transform *= get_transform();
    state.m_texture = m_texture;
    state.color = m_color;
    target.draw(m_vertices, state);
}

void Shape::set_shader(const Shader& shader)
{
    m_shader = &shader;
}

//FIX: FORMULA WRONG
glm::vec2 Shape::get_geometric_centre() const
{
    const auto count = get_point_count();

    switch (count)
    {
    case 0:
        assert(false && "Cannot calculate geometric centre of shape with no points");
        return glm::vec2{};
    case 1:
        return get_point(0);
        break;
    case 2: 
        return (get_point(0) + get_point(1)) / 2.f;
        break;
    default:
        glm::vec2 centroid{ 0.f, 0.f };

        for (size_t i = 0; i < count; ++i)
        {
            centroid += get_point(i);
        }

        centroid /= static_cast<float>(count);
        return centroid;
    }

}