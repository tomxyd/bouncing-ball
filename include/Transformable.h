#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>

class Transformable
{
public:
	Transformable();
	~Transformable();
	void set_position(glm::vec2 position);
	void set_origin(glm::vec2 origin);
	void set_scale(glm::vec2 factors);
	glm::vec2 get_position() const;
	glm::vec2 get_origin() const;
	float get_rotation() const;
	glm::vec2 get_scale() const;
private:
	glm::vec2 origin;
	glm::vec2 position;
	glm::vec2 scale{ 1.f,1.f };
	float rotation;

};


#endif