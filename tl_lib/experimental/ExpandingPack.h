#pragma once


#include <cstddef>
#include "source/type_list.hpp"

namespace TL {
namespace experimental {


template <typename TList, std::size_t, typename TResult = type_list<>>
struct partition_before_index;

template <typename T, typename ... Tp, std::size_t I, typename TResult>
struct partition_before_index<type_list<T, Tp...>, I, TResult>
{
    using new_type_list = typename TL::impl::append_type<TResult, T>::type;
    using type = typename partition_before_index<type_list<Tp...>, I-1, new_type_list>::type;
};

template <typename T, typename ... Tp, typename TResult>
struct partition_before_index<type_list<T, Tp...>, 0, TResult>
{
    using type = TResult;
};

template <typename TList, std::size_t, typename TResult = type_list<>>
struct partition_after_index;

template <typename T, typename ... Tp, std::size_t I, typename TResult>
struct partition_after_index<type_list<T, Tp...>, I, TResult>
{
    using type = typename partition_after_index<type_list<Tp...>, I-1, TResult>::type;
};

template <typename T, typename ... Tp, typename TResult>
struct partition_after_index<type_list<T, Tp...>, 0, TResult>
{
    using type = typename TL::impl::append_types<TResult, Tp...>::type;
};

template <typename TList, std::size_t I, typename TResult = type_list<>>
struct partition_without_index;

template <typename T, typename ... Tp, std::size_t I, typename TResult>
struct partition_without_index<type_list<T, Tp...>, I, TResult>
{
    using new_type_list = typename TL::impl::append_type<TResult, T>::type;
    using type = typename  partition_without_index<type_list<Tp...>, I-1, new_type_list>::type;
};

template <typename T, typename ... Tp, typename TResult>
struct partition_without_index<type_list<T, Tp...>, 0, TResult>
{
    using type = typename TL::impl::append_types<TResult, Tp...>::type;
};


template <typename TList, std::size_t I>
struct partition_by_index
{
    using type = typename get_type<TList, I>::type;
    using list_before_index = typename partition_before_index<TList, I>::type;
    using list_after_index = typename partition_after_index<TList, I>::type;
    using list_without_index = typename partition_without_index<TList, I>::type;
};

template <typename TList, typename T, std::size_t I>
struct replace
{
    using list_before = typename partition_before_index<TList, I>::type;
    using list_after = typename partition_after_index<TList, I>::type;
    using list_with_type = typename partition_without_index<TList, I>::type;
    using type = typename get_type<TList, I>::type;
};

template <typename TList, typename TResult = type_list<>>
struct reverse;

template <typename T, typename ... Tp, typename TResult>
struct reverse<type_list<T, Tp...>, TResult>
{
    using new_type_list = typename TL::impl::prepend_type<TResult, T>::type;
    using type = typename reverse<type_list<Tp...>, new_type_list>::type;
};

template <typename TResult>
struct reverse<type_list<>, TResult>
{
    using type = TResult;
};



}
}












