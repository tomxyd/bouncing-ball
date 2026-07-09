#include "VertexArray.h"


VertexArray::VertexArray(PrimitiveType type, std::size_t vertex_count) : m_vertices(vertex_count), m_primitive_type(type)
{
    ResourceManager::LoadShader(RESOURCES_PATH "sprite_vertex.glsl", RESOURCES_PATH "sprite_fragment.glsl", "shader1");

}

void VertexArray::draw(RenderTarget& target, RenderState state) const
{
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

void VertexArray::clear()
{
    m_vertices.clear();
}

void VertexArray::resize(std::size_t count)
{
    m_vertices.resize(count);
}
