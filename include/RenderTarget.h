#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "Vertex.h"
#include "Drawable.h"
#include "Shader.h"
#include "RenderState.h"
#include <OpenGL.h>
#include <Glm.h>

/* TO DO:
class VertexBuffer
{
public:
	VertexBuffer() = default;
private:
	unsigned int m_buffer;
};*/

class RenderTarget
{
public:
	~RenderTarget();
	void clear();
	void draw(const Vertex* vertices, const RenderState& state = RenderState::default);
	//void draw(const VertexBuffer& vertexBuffer, const RenderState& state = RenderState::default);
	void draw(const Drawable& drawable, const RenderState& state = RenderState::default);
private:
	void setup_draw(const RenderState& state);
	void apply_shader(const Shader* shader);
	unsigned int vertex_array;
	unsigned int vertex_buffer;
};


#endif