#include "Sprite.h"

void Sprite::load_shader() 
{
    ResourceManager::LoadShader(RESOURCES_PATH "sprite_vertex.glsl", RESOURCES_PATH "sprite_fragment.glsl", "shader1");

    this->shader = &ResourceManager::GetShader("shader1");
}


Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &element_buffer);

}

glm::vec2 Sprite::get_local_bound() const
{
    //TO DO: WRONG CALCULATION
    return { get_position().x + 1.0f, get_position().y + 1.0f};
}

void Sprite::set_color(glm::vec3 color)
{
    this->color = color;
}

Sprite::Sprite(const Texture& texture)
{
    set_position(glm::vec2(640.f, 360.f));

    load_shader();

    this->texture = &texture;
    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &element_buffer);

    glBindVertexArray(vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Sprite::draw(glm::mat4& ortho) const
{
    // prepare transformations
    this->shader->use();
    glm::mat4 model = glm::mat4(1.0f);


    model = glm::translate(model, glm::vec3(get_position(), 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * get_scale().x, 0.5f * get_scale().y, 0.0f));
    model = glm::rotate(model, glm::radians(get_rotation()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * get_scale().x, -0.5f * get_scale().y, 0.0f));
    model = glm::scale(model, glm::vec3(get_scale(), 1.0f));

    this->shader->setMat4("projection", ortho);
    this->shader->setMat4("model", model);
    this->shader->setVec3("spriteColor", color);

    //glActiveTexture(GL_TEXTURE0);
    //texture->bind_texture();

    glBindVertexArray(vertex_array);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}