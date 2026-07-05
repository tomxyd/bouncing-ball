#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "Vertex.h"
#include "Drawable.h"
#include "Shader.h"
#include "RenderState.h"
#include "PrimitiveType.h"
#include <OpenGL.h>
#include <cstddef>
#include <cstdint>
#include <Glm.h>

class Drawable; // this is needed to compile, why

class RenderTarget
{
public:
	~RenderTarget();
	void clear();
	void draw(const Vertex* vertices, std::size_t vertex_count, PrimitiveType type, const RenderState& state = RenderState::Default);
	void draw(const Drawable& drawable, const RenderState& state = RenderState::Default);
private:
	void setup_draw(const RenderState& state);
	void apply_shader(const Shader* shader);
	void draw_primitive(PrimitiveType type, std::size_t first_vertex, std::size_t vertex_count);
	unsigned int vertex_array;
	unsigned int vertex_buffer;
};
#endif // RENDER_TARGET_H