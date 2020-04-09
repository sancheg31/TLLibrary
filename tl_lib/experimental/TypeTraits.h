#pragma once

#include <cstddef>

#include "NullType.h"

namespace TL {
namespace experimental {

    struct false_argument
    {
        enum { value = 0 };
    };

    struct true_argument
    {
        enum { value = 1 };
    };

    template <typename T, typename U>
    struct is_same: false_argument{ };

    template <typename T>
    struct is_same<T, T>: true_argument { };

    template <typename T, typename U>
    inline constexpr static bool is_same_v = is_same<T, U>::value;

    template <typename T>
    struct invalid_argument
    {
        static_assert(!is_same_v<T, NullType>, "NullType is an invalid template argument");
    };

    template <std::size_t N>
    struct index_out_of_range
    {
        static_assert(N > 0, "Index is out of range");
    };

} //experimental
} //tl
