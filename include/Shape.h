#ifndef SHAPE_H
#define SHAPE_H

#include "Texture.h"
#include <Shader.h>
#include "Window.h"
#include "helper_library.h"
#include "ResourceManager.h"
#include "Transformable.h"
#include "VertexArray.h"
#include <Color.h>


class Window;

class Shape : public Drawable, public Transformable
{
public:
	//construct sprite from a source texture
	Shape() = default;
	~Shape() = default;
	glm::vec2 get_local_bound() const;
	void set_color(Color color);
	virtual std::size_t get_point_count() = 0;
	virtual glm::vec2 get_point(size_t index) = 0;
	void set_shader(const Shader& shader);
protected:
	void update();


private:
	void draw(RenderTarget& target, RenderState state) const override;
	VertexArray m_vertices{ PrimitiveType::TriangleFan };
	const Texture* m_texture = nullptr;
	const Shader* m_shader = nullptr;
	Color m_color{ Color::White };
	//declared to call sprite's draw method
	friend class Window;
};

#endif