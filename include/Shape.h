#ifndef SHAPE_H
#define SHAPE_H
#include "Texture.h"
#include <Shader.h>
#include "Window.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp> 
#include "helper_library.h"
#include "ResourceManager.h"
#include "Transformable.h"


class Window;

class Shape : public Transformable
{
public:
	//construct sprite from a source texture
	explicit Shape(const float& radius);
	glm::vec2 get_local_bound() const;
	void set_color(glm::vec3 color);
	virtual size_t get_point_count() const = 0;
	virtual glm::vec2 get_point(size_t index) = 0;
	~Shape();


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
	//declared to call sprite's draw method
	friend class Window;
};

#endif