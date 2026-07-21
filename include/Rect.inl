#include <Rect.h>  

template <typename T>  
constexpr Rect<T>::Rect(glm::vec<2, T> the_position, glm::vec<2, T> the_size) : position(the_position), size(the_size) {}