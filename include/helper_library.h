#ifndef HELPER_LIBRARY_H
#define HELPER_LIBRARY_H
#include <stdexcept>
#include <string>

namespace Tomxy
{
	inline void error(const std::string& s)
	{
		throw std::runtime_error(s);
	}
}
#endif