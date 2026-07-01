#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "Shape.h"

class Window;

class CircleShape : Shape
{
public:
	std::size_t get_point_count() override;
	glm::vec2 get_point(size_t index) override;


private:
	float radius;
	size_t count = 0;
};

#endif