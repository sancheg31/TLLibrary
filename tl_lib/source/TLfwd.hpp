#pragma once

#include "TLPredefinedHeaders.hpp"

//type_list
namespace TL {

    struct NullType;
    
    template <typename ... Tp>
    struct type_list;

    template <typename T, typename U>
    struct TypePair;

    template <auto ... Values>
    struct IndexList;

    template <typename TList>
    struct length;

    template <typename TList>
    struct empty;

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


    template <typename TList, std::size_t I, std::size_t J>
    struct swap;

    template <typename TList1, typename TList2>
    struct append;

    template <typename TList1, typename TList2>
    struct prepend;

    template <typename TList, typename Type>
    struct push_back;

    template <typename TList, typename Type>
    struct push_front;

    template <typename TList>
    struct pop_back;

    template <typename TList>
    struct pop_front;

    template <typename TIter1, typename TIter2>
    struct erase;

    template <typename TList, typename Type, std::size_t Index>
    struct set_type;

    namespace impl {

        template <typename TList>
        struct length_impl;

        template <typename TList>
        struct empty_impl;

        template <typename TList, std::size_t N, std::size_t Index = 0>
        struct get_type_impl;

        template <typename TList, typename Type>
        struct has_type_impl;

        template <typename TList, typename Type, std::size_t I = 0>
        struct type_index_impl;

        template <typename TList, typename Type, std::size_t I = 0, int Position = -1>
        struct last_type_index_impl;

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


        template <typename TList, std::size_t I, std::size_t J>
        struct swap_impl;

        template <typename TList1, typename TList2>
        struct append_impl;

        template <typename TList1, typename TList2>
        struct prepend_impl;

        template <typename TList, typename TResult = type_list<>>
        struct pop_back_impl;

        template <typename TList>
        struct pop_front_impl;

        template <typename TList, std::size_t I, typename TResult = type_list<>>
        struct list_before_index;

        template <typename TList, std::size_t I, typename TResult = type_list<>>
        struct list_after_index;

        template <typename TList, std::size_t I, typename TResult = type_list<>>
        struct list_without_index;

        template <typename TList, std::size_t I, std::size_t Length = length<TList>::value>
        struct partition_by_index;


        template <typename TList, typename Type, std::size_t Index>
        struct set_type_impl;

        template <typename TList, std::size_t I, std::size_t J>
        struct erase_impl;

        template <typename TSourceList, typename TDestList, std::size_t I, std::size_t Length>
        struct append_type_if_not_at_end;

    } //impl

    namespace traits {

        struct true_argument;

        struct false_argument;

        template <typename TList>
        struct is_type_list;

        template <typename TList>
        struct is_plain_type;

        template <typename TIter>
        struct is_iterator;

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

        template <typename ... TLists>
        struct is_type_list;

        template <typename ... Types>
        struct is_not_nulltype;

        template <typename ... TIters>
        struct is_iterator;

        template <typename ...Types>
        struct is_same;

        template <class T>
        struct has_result_type;

        template <class T>
        struct has_value_type;

        template <class T>
        struct has_type_alias;

        template <class T>
        struct has_value_variable;

        template <std::size_t X, std::size_t Y, template <class = decltype(X)> class Relation>
        struct satisfies_relation;

    } //requires

} //tl





















