#pragma once


#include <cstddef>

#include "source/type_list.h"

namespace TL {
namespace experimental {

    using empty_list = type_list<>;
    using integrals = type_list<char, short int, int, long int>;
    using floats = type_list<float, double>;

} //literals
} //tl
