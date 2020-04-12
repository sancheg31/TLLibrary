#pragma once

#include <cstddef>

//type_list
namespace TL {

    struct NullType;

    template <typename T, typename U>
    struct TypeList;

    template <typename ... Tp>
    struct type_list;

    template <typename TList>
    constexpr int size();

    template <typename ... Tp>
    constexpr int size(type_list<Tp...>&&);

    template <typename TList>
    struct length;

    template <typename TList>
    struct empty;

    template <typename TList>
    struct first_type;

    template <typename TList>
    struct last_type;

    template <typename TList1, typename TList2>
    struct equal;

    template <typename TList, typename T>
    struct type_count;

    template <typename TList, std::size_t N>
    struct get_type;

    template <typename TList>
    struct first_type;

    template <typename TList>
    struct last_type;

    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct type_index;

    template <typename TList, typename Type>
    struct last_type_index;

    template <typename TList, template <class> class Property>
    struct find_type;

    template <typename TList, template <class> class UnPred>
    struct all_of;

    template <typename TList, template <class> class UnPred>
    struct any_of;

    template <typename TList, template <class> class UnPred>
    struct none_of;

    template <typename TList1, typename TList2>
    struct equal;

    template <typename TList1, typename TList2>
    struct not_equal;

    template <typename TList1, typename TList2>
    struct append;

    template <typename TList1, typename TList2>
    struct prepend;

    template <typename TList, typename Type>
    struct push_back;

    template <typename TList, typename Type>
    struct push_front;

    namespace impl {

        template <typename TList>
        struct length_impl;

        template <typename TList>
        struct empty_impl;

        template <typename TList, typename Type>
        struct type_count_impl;

        template <typename TList, std::size_t N, std::size_t Index = 0>
        struct get_type_impl;

        template <typename TList, typename Type>
        struct has_type_impl;

        template <typename TList, typename Type, std::size_t I = 0>
        struct type_index_impl;

        template <typename TList, typename Type, std::size_t I = 0, int Position = -1>
        struct last_type_index_impl;

        template <typename TList, template <class> class Property>
        struct find_type_impl;


        template <typename TList, template <class> class UnPred>
        struct all_of_impl;

        template <typename TList, template <class> class UnPred>
        struct any_of_impl;

        template <typename TList, template <class> class UnPred>
        struct none_of_impl;


        template <typename TList1, typename TList2, std::size_t N = length<TList1>::value, std::size_t I = 0>
        struct equal_impl;

        template <typename TList, typename T>
        struct append_type;

        template <typename TList, typename ... Tp>
        struct append_types;

        template <typename TList1, typename TList2>
        struct append_list;


        template <typename TList, typename T>
        struct prepend_type;

        template <typename TList, typename ... Tp>
        struct prepend_types;

        template <typename TList1, typename TList2>
        struct prepend_list;


        template <typename TList1, typename TList2>
        struct append_impl;

        template <typename TList1, typename TList2>
        struct prepend_impl;

    } //impl

    namespace traits {

        struct true_argument;

        struct false_argument;

        template <typename TList>
        struct is_type_list;

        template <typename TList>
        struct is_plain_type;

        template <class T>
        struct has_result_type;

        template <class T>
        struct has_value_type;

        template <class T>
        struct has_type_alias;

        template <typename T, typename U>
        struct is_same;

    } //traits

    namespace utilities {

        template <typename IllegalType>
        struct invalid_argument;

        template <typename ActualType, typename IllegalType>
        struct is_valid_argument;

        template <typename Type>
        struct type_or_list;

        template <std::size_t N>
        struct index_out_of_range;

    } //utilities

    namespace requires {

        template <typename TList>
        struct is_type_list;

        template <typename TList>
        struct is_plain_type;

        template <class T>
        struct has_result_type;

        template <class T>
        struct has_value_type;

        template <class T>
        struct has_type_alias;

        template <class T>
        struct has_value_variable;

        template <typename Type>
        struct is_not_nulltype;

        template <int X, int Y, template <class> class Relation>
        struct satisfies_relation;

    } //requires

} //tl





















