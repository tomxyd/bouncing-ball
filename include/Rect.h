#ifndef RECT_H
#define RECT_H

#include <Glm.h>

template <typename T>
class Rect
{
public:
	Rect() = default;
	constexpr Rect(glm::vec<2, T> position, glm::vec<2, T> size);
	glm::vec2 position{};
	glm::vec2 size{};

};

using IntRect = Rect<int>;
using FloatRect = Rect<float>;

#include "Rect.inl"

#endif