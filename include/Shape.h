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
#include <Rect.h>


class Window;

class Shape : public Drawable, public Transformable
{
public:
	//construct sprite from a source texture
	Shape() = default;
	~Shape() = default;
	FloatRect get_local_bound() const;
	FloatRect get_global_bound() const;
	glm::vec2 get_geometric_centre() const;
	void set_color(Color color);
	virtual std::size_t get_point_count() const = 0;
	virtual glm::vec2 get_point(size_t index) const = 0;
	void set_shader(const Shader& shader);
	
protected:
	void update();


private:
	void draw(RenderTarget& target, RenderState state) const override;
	VertexArray m_vertices{ PrimitiveType::TriangleFan };
	const Texture* m_texture = nullptr;
	const Shader* m_shader = nullptr;
	FloatRect m_bounds;
	Color m_color{ Color::White };
	//declared to call sprite's draw method
	friend class Window;
};

#endif