#include <iostream>
#include <concepts>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

class Figure{
    private:
    

}