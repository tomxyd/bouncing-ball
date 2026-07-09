#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "Shape.h"

class Window;

class CircleShape : public Shape
{
public:
	explicit CircleShape(float radius = 0, std::size_t point_count = 30);
	std::size_t get_point_count() override;
	glm::vec2 get_point(size_t index) override;


private:
	float m_radius;
	std::size_t m_point_count = 0;
};

#endif