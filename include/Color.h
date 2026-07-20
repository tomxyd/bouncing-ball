#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color
{
public:
	constexpr Color() = default;
	constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) :
		r(red), g(green), b(blue), a(alpha) 
	{
	}

	//static-member data
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;

	std::uint8_t r{};
	std::uint8_t g{};
	std::uint8_t b{};
	std::uint8_t a{255};

};


#endif