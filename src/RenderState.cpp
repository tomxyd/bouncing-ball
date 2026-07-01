#include "RenderState.h"

const RenderState RenderState::default = RenderState();


RenderState::RenderState(const Shader* shader)
{
	m_shader = shader;
}