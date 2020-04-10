#pragma once

#include "TLUtility.hpp"

namespace TL {

    template <typename ... Tp>
    struct type_list;

namespace requires {

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

    template <typename Type>
    struct is_not_nulltype;

    template <typename Type>
    struct is_not_nulltype
    {
        static_assert(!utilities::is_same_v<NullType, Type>, "NullType is an invalid template argument");
    };

    template <std::size_t I, std::size_t N, template <std::size_t, std::size_t> class Relation>
    struct is_satisfy_relation;

    template <std::size_t I, std::size_t N>
    struct less_than
    {
        static_assert(I < N, "index is out of range");
    };

} //requires
} //tl

