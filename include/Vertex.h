#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include "Color.h"


struct Vertex
{
	glm::vec2 position;
	Color color{};
	glm::vec2 texCoords{};
};


#endif