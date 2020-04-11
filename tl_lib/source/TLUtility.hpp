#pragma once

#include "TLfwd.hpp"
#include "TLTraits.hpp"

namespace TL {
namespace utilities {

    /*
     * Forward declaration
     * */
    template <typename IllegalType>
    struct invalid_argument;

    template <typename Illegal>
    struct invalid_argument
    {
    private:
        struct InnerType { };
        static_assert(traits::is_same<Illegal, InnerType>::value, "invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <typename ActualType, typename IllegalType>
    struct is_valid_argument;

    template <typename Actual, typename Illegal>
    struct is_valid_argument
    {
        static_assert(!traits::is_same<Actual, Illegal>::value, "invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <typename Type>
    struct type_or_list;

    template <typename Type>
    struct type_or_list
    {
        using result = Type;
    };

    template <typename ... Tp>
    struct type_or_list<type_list<Tp...>>
    {
        using result = typename type_list<Tp...>::result_type;
    };


    /*
     * Forward declaration
     * */
    template <std::size_t N>
    struct index_out_of_range;

    template <std::size_t N>
    struct index_out_of_range
    {
        static_assert(N == 0, "Index is out of range");
    };


} //utilities
} //tl
