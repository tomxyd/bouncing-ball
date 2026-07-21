#include "VertexArray.h"


VertexArray::VertexArray(PrimitiveType type, std::size_t vertex_count) : m_vertices(vertex_count), m_primitive_type(type)
{
}

void VertexArray::draw(RenderTarget& target, RenderState state) const
{

    //state.m_transform *= getTransform();
    state.m_shader = &ResourceManager::GetShader("shader1");
	if (!m_vertices.empty())
		target.draw(m_vertices.data(), m_vertices.size(), m_primitive_type, state);
}

Vertex& VertexArray::operator[](std::size_t index)
{
    assert(index < m_vertices.size() && "Index is out of bounds");
    return m_vertices[index];
}

const Vertex& VertexArray::operator[](std::size_t index) const
{
    assert(index < m_vertices.size() && "Index is out of bounds");
    return m_vertices[index];
}

FloatRect VertexArray::get_bounds() const
{
    if (!m_vertices.empty())
    {
        float left = m_vertices[0].position.x;
        float top = m_vertices[0].position.y;
        float right = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;


        for (std::size_t i = 1; i < m_vertices.size(); ++i)
        {
            const glm::vec2 position = m_vertices[i].position;

            if (position.x < left)
            {
                left = position.x;
            }
            else if (position.x > right)
            {
                right = position.x;
            }

            if (position.y < top)
            {
                top = position.y;
            }
            else if (position.y > bottom)
            {
                bottom = position.y;
            }
        }

        return { {left, top}, {right - left, bottom - top} };

    }

    return {};
}

void VertexArray::clear()
{
    m_vertices.clear();
}

void VertexArray::resize(std::size_t count)
{
    m_vertices.resize(count);
}
