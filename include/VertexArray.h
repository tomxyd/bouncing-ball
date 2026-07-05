#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <Drawable.h>
#include <Vertex.h>
#include <Vector>
#include "PrimitiveType.h"

/*
*  class VertexArray
*  'VertexArray' is a simple wrapper around a dynamic 
*	array of vertices and primitive types
* 
*	It inherits 'Drawable', but unlike other drawables
*	it is not transformable
* 
*	Test example code:
*	VertexArray lines(PrimitiveType::LineStrip, 4);
*	lines[0].position = sf::Vector2f(10, 0);
*	lines[1].position = sf::Vector2f(10, 0);
*	lines[2].position = sf::Vector2f(10, 0);
*	lines[3].position = sf::Vector2f(10, 0);
* 
*	window.draw(lines);
*/

class VertexArray: public Drawable
{
public:
	// Creates an empty vertex array
	VertexArray() = default;
	VertexArray(PrimitiveType type, std::size_t vertex_count);
	Vertex& VertexArray::operator[](std::size_t index);
	const Vertex& VertexArray::operator[](std::size_t index) const;

private:
	void draw(RenderTarget& target, RenderState state) const override;
	std::vector<Vertex> m_vertices;
	PrimitiveType m_primitive_type{ PrimitiveType::Points };
};

#endif