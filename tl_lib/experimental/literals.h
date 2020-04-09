#pragma once


#include <cstddef>
#include "type_list.h"


namespace TL {
namespace experimental {

    using empty_list = type_list<>;
    using integrals = type_list<int8_t, int16_t, int32_t, int64_t>;
    using floats = type_list<float, double>;

} //literals
} //tl
