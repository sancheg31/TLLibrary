#pragma once

#include <cstddef>
#include <type_traits>

#include "tl_node.h"
#include "tl_traits.h"

namespace TL {

template <typename TList>
struct type_list_wrapper;

template <typename TList>
struct type_list_wrapper: TList
{
    using self_type = type_list_wrapper<TList>;
    using result_type = TList;
};

template <typename ... Tp>
struct make_type_list;

template <typename T, typename ... Tp>
struct  make_type_list<T, Tp...>
{
    using sub_type = Implementation::TypeList<T, typename make_type_list<Tp...>::sub_type>;
    using type = type_list_wrapper<sub_type>;
};

template <typename T, typename U>
struct  make_type_list<Implementation::TypeList<T, U>>
{
    using sub_type = Implementation::TypeList<T, typename make_type_list<U>::sub_type>;
    using type = type_list_wrapper<sub_type>;
};

template <typename T>
struct  make_type_list<Implementation::SingletonList<T>>
{
    using sub_type = Implementation::SingletonList<T>;
    using type = type_list_wrapper<sub_type>;
};

template <>
struct  make_type_list<>
{
    using sub_type = Implementation::EmptyList;
    using type = type_list_wrapper<sub_type>;
};

template <typename ... Tp>
using type_list = typename make_type_list<Tp...>::type;


template <typename TList>
 constexpr int size() {
    return Implementation::size<typename TList::result_type>::value;
}

template <typename TList>
 constexpr int size(TList &&) {
    return Implementation::size<typename TList::result_type>::value;
}


template <typename TList, typename T>
struct type_count;

template <typename TList, typename T>
struct type_count;

template <typename TList, typename T>
struct  type_count
{
    enum { value =  Implementation::type_count<typename TList::result_type, T>::value };
};

template <typename TList>
struct empty;

template <typename TList>
struct  empty
{
    enum { value = false };
};

template <>
struct empty<type_list_wrapper<Implementation::EmptyList>>
{
    enum { value = true };
};


template <typename TList, std::size_t N>
struct get_type;

template <typename TList, typename Type>
struct has_type;


template <typename TList, std::size_t N>
struct  get_type
{
    using type = typename Implementation::get_type<typename TList::result_type, N>::type;
};


template <typename TList, typename Type>
struct  has_type
{
    enum { value = Implementation::has_type<typename TList::result_type, Type>::value };
};


template <typename T, typename U, bool first = utilities::has_result_type_v<T>,
                                    bool second = utilities::has_result_type_v<U>>
struct append_impl;

template <typename T, typename U>
struct append_impl<T, U, true, true>
{
    using type = typename Implementation::append_list<typename T::result_type, typename U::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, true, false>
{
    using type = typename Implementation::append_list<typename T::result_type, typename type_list<U>::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, false, true>
{
    using type = typename Implementation::append_list<typename type_list<T>::result_type, typename U::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, false, false>
{
    using type = typename Implementation::append_list<typename type_list<T>::result_type, typename type_list<U>::result_type>::type;
};

template <typename TList1, typename TList2>
struct append;

template <typename TList1, typename TList2>
struct  append
{
    using type = type_list<typename append_impl<TList1, TList2>::type>;
};


template <typename TList>
inline constexpr bool empty_v = empty<TList>::value;

template <typename TList, typename Type>
inline constexpr bool has_type_v = has_type<TList, Type>::value;

template <typename TList, typename Type>
inline constexpr bool type_count_v = type_count<TList, Type>::value;

template <typename TList, std::size_t N>
using get_type_t = typename get_type<TList, N>::type;

template <typename T, typename U>
using append_t = typename append<T, U>::type;

} //tl




