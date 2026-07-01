#include "CircleShape.h"


std::size_t CircleShape::get_point_count() 
{
	return count;
}

glm::vec2 CircleShape::get_point(size_t index) 
{
	return glm::vec2({ 1.0f, 1.0f });
}
