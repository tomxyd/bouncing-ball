#include "Sprite.h"

glm::vec2 Sprite::get_local_bound() const
{
    //TO DO: WRONG CALCULATION
    return { get_position().x + 1.0f, get_position().y + 1.0f};
}

void Sprite::set_color(const Color& color)
{
    this->m_color = color;
}

Sprite::Sprite(const Texture& texture)
{
    update_vertices();

    set_position(glm::vec2(640.f, 360.f));

    this->m_texture = &texture;
}


void Sprite::draw(RenderTarget& target, RenderState state) const
{
    state.m_texture = m_texture;
    target.draw(m_vertices.data(), m_vertices.size(), PrimitiveType::Triangles, state);
}

void Sprite::update_vertices()
{
    m_vertices[0].position = { 0.f,1.0f };
    m_vertices[1].position = { 1.f,0.f };
    m_vertices[2].position = { 0.f,0.f };
    m_vertices[3].position = { 0.f,1.0f };
    m_vertices[4].position = { 1.f,1.0f };
    m_vertices[5].position = { 1.f,0.0f };


    m_vertices[0].texCoords = { 0.f,1.0f };
    m_vertices[1].texCoords = { 1.f,0.f };
    m_vertices[2].texCoords = { 0.f,0.f };
    m_vertices[3].texCoords = { 0.f,1.0f };
    m_vertices[4].texCoords = { 1.f,1.0f };
    m_vertices[5].texCoords = { 1.f,0.0f };
}

