#include "Transformable.h"

Transformable::Transformable()
{
	rotation = 0.0f;
}

Transformable::~Transformable()
{

}


void Transformable::set_position(glm::vec2 position)
{
	this->position = position;
}

void Transformable::set_origin(glm::vec2 origin)
{
	this->origin = origin;
}

void Transformable::set_scale(glm::vec2 factors)
{
	this->scale = factors;
}

glm::vec2 Transformable::get_position() const
{
	return position;
}

glm::vec2 Transformable::get_origin() const
{
	return origin;
}

float Transformable::get_rotation() const
{
	return rotation;
}

glm::vec2 Transformable::get_scale() const
{
	return scale;
}