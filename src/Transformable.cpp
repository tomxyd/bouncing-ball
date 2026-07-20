#include "Transformable.h"


void Transformable::set_position(glm::vec2 position)
{
	m_position = position;
	m_transform_needs_updated = true;
}

void Transformable::set_origin(glm::vec2 origin)
{
	m_origin = origin;
	m_transform_needs_updated = true;

}

void Transformable::set_rotation(float angle)
{
	m_rotation = angle;
	m_transform_needs_updated = true;

}

void Transformable::set_scale(glm::vec2 factors)
{
	m_scale = factors;
	m_transform_needs_updated = true;

}

glm::vec2 Transformable::get_position() const
{
	return m_position;
}

glm::vec2 Transformable::get_origin() const
{
	return m_origin;
}

float Transformable::get_rotation() const
{
	return rotation;
}

glm::vec2 Transformable::get_scale() const
{
	return m_scale;
}

const Transform& Transformable::getTransform() const
{
	if (m_transform_needs_updated)
	{
		const float angle = glm::radians(-m_rotation);
		const float cosine = glm::cos(angle);
		const float sine = glm::sin(angle);
		const float sxc = m_scale.x * cosine;
		const float syc = m_scale.y *cosine;
		const float sxs = m_scale.x *sine;
		const float sys = m_scale.y *sine;
		const float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
		const float ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

		// clang-format off
		m_transform = Transform(sxc, sys, tx,
			-sxs, syc, ty,
			0.f, 0.f, 1.f);
		// clang-format on
		m_transform_needs_updated = false;
	}

	return m_transform;
}