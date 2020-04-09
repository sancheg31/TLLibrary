#pragma once

#include "NullType.h"

namespace TL {
namespace experimental {

    /*
     * Forward declaration.
     * */
    template <typename T, typename U>
    struct TypeList;

    /*
     * Common case.
     * */
    template <typename T, typename ... Tp>
    struct TypeList<T, TypeList<Tp...>>
    {
        using Current = T;
        using Next = TypeList<Tp...>;
    };

    /*
     * NullType is not allowed as a type.
     * */
    template <typename ... Tp>
    struct TypeList<NullType, TypeList<Tp...>>;

    /*
     * End of the list
     * */
    template <typename T>
    struct TypeList<T, NullType>
    {
        using Current = T;
        using Next = NullType;
    };

    /*
     * Empty list
     * */
    template <>
    struct TypeList<NullType, NullType>
    {
        using Current = NullType;
        using Next = NullType;
    };

    /*
     * alias for one element list.
     * */
    template <typename T>
    using SingletonList = TypeList<T, NullType>;

    /*
     * alias for zero element list
     * */
    using EmptyList = TypeList<NullType, NullType>;

} //experimental
} //tl
