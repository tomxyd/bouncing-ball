#ifndef SPRITE_H
#define SPRITE_H
#include "Texture.h"
#include "Window.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp> 
#include "helper_library.h"
#include "ResourceManager.h"
#include "Transformable.h"
#include "Color.h"
#include "Vertex.h"
#include "Drawable.h"
#include <array>
#include "RenderState.h"


class Window;

class Sprite : public Drawable, public Transformable
{
public:
	//construct sprite from a source texture
	explicit Sprite(const Texture& texture);
	glm::vec2 get_local_bound() const;
	void set_color(const Color& color);
	~Sprite();


private:
	void draw(RenderTarget& target, RenderState state) const override;
	void update_vertices();
	void load_shader();
	const Texture* m_texture;
	const Shader* m_shader;
	Color m_color;
	std::array<Vertex, 6> m_vertices;
	friend class Window;
};

#endif