#include "CircleShape.h"

explicit CircleShape::CircleShape(const float& radius)
{
	this->radius = radius;
}

CircleShape::~CircleShape()
{

}

std::size_t CircleShape::get_point_count() const override
{

}

glm::vec2 CircleShape::get_point(size_t index) const override
{

}
