#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
    default_shader = &ResourceManager::GetShader("shader1");
}

RenderTarget::~RenderTarget()
{

}

void RenderTarget::clear()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &vertex_array);
}


void RenderTarget::draw(const Vertex* vertices, const std::size_t vertex_count, PrimitiveType type, const RenderState& state)
{
	// generate vertex buffer and bind m_vertices to the buffer data
	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &vertex_buffer);

    //pre-transform the vertex data into global coordinate system
    std::array<Vertex, 4> m_cache;
    bool use_cache_data = vertex_count <= m_cache.size();

    if (use_cache_data)
    {
        glm::mat4 transform = glm::mat4(1.0f);
        {
            for (std::size_t i = 0; i < vertex_count; ++i)
            {
                Vertex& vertex = m_cache[i];
                glm::vec4 p(vertices[i].position.x,
                    vertices[i].position.y,
                    0.0f,
                    1.0f);
                glm::vec4 result = transform * p;
                vertex.position = glm::vec2(result.x, result.y);
                vertex.color = vertices[i].color;
                vertex.texCoords = vertices[i].texCoords;
                m_cache[i] = vertex;
            }
        }
    }


    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    if (use_cache_data)
    {
        glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), m_cache.data(), GL_STATIC_DRAW);
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    }

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
    
    draw_primitive(type, 0, vertex_count);

}

void RenderTarget::draw(const Drawable& drawable, const RenderState& state)
{
	drawable.draw(*this, state);
}

void RenderTarget::set_viewport(glm::vec2& size)
{
    viewport_size = size;
}


void RenderTarget::setup_draw(const RenderState& state)  
{  
   //apply shader  
   if (state.m_shader == nullptr)  
       const_cast<const Shader*&>(state.m_shader) = default_shader;  
   apply_shader(state.m_shader);  


   //apply view  
   apply_view(state);


   state.m_shader->setMat4("model", state.m_transform.getMatrix());
 
   glm::vec3 color = glm::vec3(state.color.r, state.color.g, state.color.b); 
   state.m_shader->setVec3("spriteColor", color);  

   //apply blend mode  

   //apply texture  
   bool hasTexture = false;
   if (state.m_texture)
   {
       glActiveTexture(GL_TEXTURE0);
       state.m_texture->bind_texture();
       hasTexture = true;
   }
   state.m_shader->setBool("hasTexture", hasTexture);
}

void RenderTarget::apply_view(const RenderState& state)
{
    glViewport(0, 0, viewport_size.x, viewport_size.y);

    glm::mat4 ortho = glm::ortho(0.0f, viewport_size.x, viewport_size.y, 0.0f, -1.f, 1.f);

    state.m_shader->setMat4("projection", ortho);
}

void RenderTarget::apply_shader(const Shader* shader)
{
    if(shader)
        Shader::bind(shader);
}


void RenderTarget::draw_primitive(PrimitiveType type, std::size_t first_vertex, std::size_t vertex_count)
{
    GLenum mode{};
    switch (type)
    {
    case PrimitiveType::LineStrip:
        mode = GL_LINE_STRIP;
        break;
    case PrimitiveType::Triangles:
        mode = GL_TRIANGLES;
        break;
    case PrimitiveType::Points:
        mode = GL_POINTS;
        break;
    case PrimitiveType::TriangleFan:
        mode = GL_TRIANGLE_FAN;
        break;
    }

    // Draw the primitives
    glDrawArrays(mode, static_cast<GLint>(first_vertex), static_cast<GLsizei>(vertex_count));
}