#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "Shape.h"

class Window;

class CircleShape : public Transformable, public Shape
{
public:
	//construct sprite from a source texture
	explicit CircleShape(const float& radius);
	std::size_t get_point_count() const override;
	glm::vec2 get_point(size_t index) const override;
	~CircleShape();


private:
	void draw(glm::mat4& ortho) const;
	void load_shader();
	unsigned int vertex_array;
	unsigned int vertex_buffer;
	unsigned int element_buffer;
	const Texture* texture = nullptr;
	const Shader* shader;
	glm::vec3 color;
	float radius;
	size_t count = 0;
	//declared to call sprite's draw method
	friend class Window;
};

#endif