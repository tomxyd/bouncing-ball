#include "RenderTarget.h"



RenderTarget::~RenderTarget()
{

}

void RenderTarget::clear()
{

}


void RenderTarget::draw(const Vertex* vertices, const RenderState& state)
{
	// generate vertex buffer and bind m_vertices to the buffer data
	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &vertex_buffer);


	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);



    glBindVertexArray(vertex_array);
    glVertexAttribPointer(
        0,                      // attribute index in shader
        2, GL_FLOAT, GL_FALSE,  // vec2
        sizeof(Vertex),         // stride
        (void*)offsetof(Vertex, position)
    );
    glEnableVertexAttribArray(0);

    // Attribute 1 = texCoords (vec2)
    glVertexAttribPointer(
        1,
        2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, texCoords)
    );
    glEnableVertexAttribArray(1);

    setup_draw(state);

    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void RenderTarget::draw(const VertexBuffer& vertexBuffer, const RenderState& state)
{

}

void RenderTarget::draw(const Drawable& drawable, const RenderState& state)
{

	drawable.draw(*this, state);
}


void RenderTarget::setup_draw(const RenderState& state)
{
    //apply shader
    apply_shader(state.m_shader);


	//apply view
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 ortho = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.f, 1.f);

    model = glm::translate(model, glm::vec3(200.f, 200.f, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * 10.f, 0.5f * 10.f, 0.0f));
    model = glm::rotate(model, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * 10.f, -0.5f * 10.f, 0.0f));
    model = glm::scale(model, glm::vec3(100.f, 100.f, 1.0f));

    state.m_shader->setMat4("projection", ortho);
    state.m_shader->setMat4("model", model);
    glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
    state.m_shader->setVec3("spriteColor", color);

	//apply blend mode

	//apply texture
    glActiveTexture(GL_TEXTURE0);
    if(state.m_texture)
        state.m_texture->bind_texture();


}

void RenderTarget::apply_shader(const Shader* shader)
{
    Shader::bind(shader);
}