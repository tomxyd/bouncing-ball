#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Glm.h>
#include <Rect.h>
#include <algorithm>
#include <array>

class Transform
{
public:
	explicit Transform() = default;
	const glm::mat4& getMatrix() const;
	Transform& operator=(const Transform& other);
		////////////////////////////////////////////////////////////
	/// \brief Construct a transform from a 3x3 matrix
	///
	/// \param a00 Element (0, 0) of the matrix
	/// \param a01 Element (0, 1) of the matrix
	/// \param a02 Element (0, 2) of the matrix
	/// \param a10 Element (1, 0) of the matrix
	/// \param a11 Element (1, 1) of the matrix
	/// \param a12 Element (1, 2) of the matrix
	/// \param a20 Element (2, 0) of the matrix
	/// \param a21 Element (2, 1) of the matrix
	/// \param a22 Element (2, 2) of the matrix
	///
	////////////////////////////////////////////////////////////
	Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);
	FloatRect transform_rect(const FloatRect& rectangle) const;

	Transform& combine(const Transform& transform);
	Transform& translate(glm::vec2 offset);
	Transform& scale(glm::vec2 factor);
	Transform& rotate(float angle);

private:
	glm::mat4 m_matrix = glm::mat4(1.0f);
};

inline Transform& operator*(const Transform& left, const Transform& right)
{
	Transform result = left; // Create a non-const copy of 'left'
	result.combine(right);   // Call 'combine' on the non-const copy
	return result;
}

inline Transform& operator*=(Transform& left, const Transform& right)
{
	return left.combine(right);
}



#endif