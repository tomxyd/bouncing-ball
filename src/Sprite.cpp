#include "Sprite.h"

void Sprite::load_shader() 
{
    ResourceManager::LoadShader(RESOURCES_PATH "sprite_vertex.glsl", RESOURCES_PATH "sprite_fragment.glsl", "shader1");

}


Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
}

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

    load_shader();

    this->texture = &texture;
    // set up vertex data (and buffer(s)) and configure vertex attributes
//// ------------------------------------------------------------------
//    float vertices[] = {
//        // pos      // tex
//        0.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 0.0f, 0.0f,
//
//        0.0f, 1.0f, 0.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 0.0f, 1.0f, 0.0f
//    };
//
//    glGenVertexArrays(1, &vertex_array);
//    glGenBuffers(1, &vertex_buffer);
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // position attribute
//    glBindVertexArray(vertex_array);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
}

//void Sprite::draw(glm::mat4& ortho) const
//{
//    // prepare transformations
//    this->shader->use();
//    glm::mat4 model = glm::mat4(1.0f);
//
//
//    model = glm::translate(model, glm::vec3(get_position(), 0.0f));
//    model = glm::translate(model, glm::vec3(0.5f * get_scale().x, 0.5f * get_scale().y, 0.0f));
//    model = glm::rotate(model, glm::radians(get_rotation()), glm::vec3(0.0f, 0.0f, 1.0f));
//    model = glm::translate(model, glm::vec3(-0.5f * get_scale().x, -0.5f * get_scale().y, 0.0f));
//    model = glm::scale(model, glm::vec3(get_scale(), 1.0f));
//
//    this->shader->setMat4("projection", ortho);
//    this->shader->setMat4("model", model);
//    //this->shader->setVec3("spriteColor", color);
//
//    glActiveTexture(GL_TEXTURE0);
//    texture->bind_texture();
//
//    glBindVertexArray(vertex_array);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}

void Sprite::draw(RenderTarget& target, RenderState state) const
{
    state.m_texture = texture;
    state.m_shader = &ResourceManager::GetShader("shader1");
    target.draw(m_vertices.data(), state);
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

