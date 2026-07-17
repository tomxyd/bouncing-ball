#include "RenderState.h"

const RenderState RenderState::Default = RenderState();


RenderState::RenderState(const Shader* shader)
{
	m_shader = shader;
}