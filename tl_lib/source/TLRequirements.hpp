#pragma once

#include "TLfwd.hpp"
#include "TLTraits.hpp"

namespace TL {
namespace requires {

    /*
     * Forward declaration
     * */
    template <typename TList>
    struct is_type_list;

    template <typename TList>
    struct is_type_list: traits::is_type_list<TList>
    {
        static_assert(is_type_list<TList>::value, "argument is not a type list");
    };


    /*
     * Forward declaration
     * */
    template <typename Type>
    struct is_not_nulltype;

    template <typename Type>
    struct is_not_nulltype
    {
        static_assert(!traits::is_same<NullType, Type>::value, "NullType is an invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <std::size_t I, std::size_t N>
    struct less_than;

    template <std::size_t I, std::size_t N>
    struct less_than
    {
        static_assert(I < N, "index is out of range");
    };

} //requires
} //tl

