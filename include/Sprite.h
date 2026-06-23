#ifndef SPRITE_H
#define SPRITE_H
#include "Texture.h"
#include <Shader.h>
#include "Window.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "helper_library.h"
#include "ResourceManager.h"


class Window;

class Sprite
{
public:
	//construct sprite from a source texture
	explicit Sprite(const Texture& texture);
	~Sprite();


private:
	void draw(glm::mat4& ortho) const;
	void load_shader();
	unsigned int vertex_array;
	unsigned int vertex_buffer;
	unsigned int element_buffer;
	const Texture* texture;
	const Shader* shader;
	//Transform abstract variables seperation
	glm::vec2 position = glm::vec2(640.f,360.f);
	glm::vec2 scale;
	glm::vec2 size = glm::vec2(100.f, 100.f);
	glm::vec3 color = glm::vec3(1.f, 0.f, 0.f);
	//declared to call sprite's draw method
	friend class Window;
};

#endif