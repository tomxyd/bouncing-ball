#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <Glm.h>
#include <Transform.h>

class Transformable
{
public:
	explicit Transformable() = default;
	virtual ~Transformable() = default;
	void set_position(glm::vec2 position);
	void set_origin(glm::vec2 origin);
	void set_scale(glm::vec2 factors);
	void set_rotation(float angle);
	glm::vec2 get_position() const;
	glm::vec2 get_origin() const;
	float get_rotation() const;
	glm::vec2 get_scale() const;
	const Transform& get_transform() const;
private:
	glm::vec2 m_origin{ 0.f, 0.f };
	glm::vec2 m_position{0.f,0.f };
	glm::vec2 m_scale{ 1.f,1.f };
	float m_rotation = 0.f;
	mutable Transform m_transform;
	mutable bool m_transform_needs_updated{ false };
	float rotation;

};


#endif