#ifndef SPRITE_H
#define SPRITE_H
#include "Texture.h"
#include <glad/glad.h>
#include <Shader.h>
#include "Window.h"
#include <glm/glm.hpp>
#include "helper_library.h"


class Window;

class Sprite
{
public:
	//construct sprite from a source texture
	Sprite(const Shader& shader, const Texture& texture);
	~Sprite();


private:
	void draw() const;
	unsigned int vertex_array;
	unsigned int vertex_buffer;
	unsigned int element_buffer;
	const Texture* texture;
	const Shader* shader;
	//Transform abstract variables seperation
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 size;
	glm::vec3 color;
	//declared to call sprite's draw method
	friend class Window;
};

#endif