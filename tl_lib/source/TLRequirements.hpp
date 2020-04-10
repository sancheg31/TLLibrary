#pragma once

#include "TLfwd.hpp"
#include "TLUtility.hpp"

namespace TL {
namespace requires {

    /*
     * Forward declaration
     * */
    template <typename TList>
    struct is_type_list;

    template <typename ... Tp>
    struct is_type_list<type_list<Tp...>> { };

    template <typename TList>
    struct is_type_list
    {
    private:
        struct InnerType { };
        static_assert(utilities::is_same_v<TList, InnerType>, "argument is not a type list");
    };


    /*
     * Forward declaration
     * */
    template <typename Type>
    struct is_not_nulltype;

    template <typename Type>
    struct is_not_nulltype
    {
        static_assert(!utilities::is_same_v<NullType, Type>, "NullType is an invalid template argument");
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

