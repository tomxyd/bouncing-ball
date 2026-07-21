#ifndef SPRITE_H
#define SPRITE_H


#include "Texture.h"
#include "Window.h"
#include "Transformable.h"
#include "Color.h"
#include "Vertex.h"
#include "Drawable.h"
#include <array>
#include "RenderState.h"
#include <Glm.h>


class Window;

class Sprite : public Transformable, public Drawable
{
public:
	//construct sprite from a source texture
	explicit Sprite(const Texture& texture);
	glm::vec2 get_local_bound() const;
	void set_color(const Color& color);
	~Sprite() = default;


private:
	void draw(RenderTarget& target, RenderState state) const override;
	void update_vertices();
	const Texture* m_texture = nullptr;
	std::array<Vertex, 6> m_vertices;
	Color m_color;
	friend class Window;
};

#endif