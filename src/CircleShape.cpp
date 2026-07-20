#include "CircleShape.h"

CircleShape::CircleShape(float radius, std::size_t point_count) : m_radius(radius), m_point_count(point_count)
{
	update();
}

std::size_t CircleShape::get_point_count() const
{
	return m_point_count;
}

glm::vec2 CircleShape::get_point(size_t index) const
{
    const float PI = 3.14159265358979323846f;
    float fraction = static_cast<float>(index) / static_cast<float>(m_point_count);
    float degrees = fraction * 360.f - 90.f;
    float radians = degrees * ( PI / 180.f);

    float x = m_radius + m_radius * std::cos(radians);
    float y = m_radius + m_radius * std::sin(radians);

    return glm::vec2(x, y);
}
