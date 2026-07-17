#ifndef RENDER_STATE_H
#define RENDER_STATE_H


#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include <Transform.h>

struct RenderState
{
public:
	RenderState() = default;
	RenderState(const Shader* shader); // FIX
	static const RenderState Default;
	const Shader* m_shader = nullptr;
	const Texture* m_texture = nullptr;
	Transform m_transform;
};

#endif