#pragma once

#include <cstddef>
#include <type_traits>

#include "tl_fwd.h"
#include "type_list_impl.h"

namespace TL {

template <typename TList>
struct type_list_wrapper: TList
{
    using self_type = type_list_wrapper<TList>;
    using result_type = TList;

    static constexpr bool isEmpty() { return TL::empty<self_type>(); };
    static constexpr int size() { return TL::size<self_type>(); }

    template <typename T>
    static constexpr bool hasType() { return TL::has_type<self_type, T>(); }

    template <typename T>
    static constexpr int typeCount() { return TL::type_count<self_type, T>(); }
};

template <typename T, typename ... Tp>
struct  make_type_list<T, Tp...>
{
    using sub_type = __TypeList<T, typename make_type_list<Tp...>::sub_type>;
    using type = type_list_wrapper<sub_type>;
};

template <typename T, typename U>
struct  make_type_list<__TypeList<T, U>>
{
    using sub_type = __TypeList<T, typename make_type_list<U>::sub_type>;
    using type = type_list_wrapper<sub_type>;
};

template <typename T>
struct  make_type_list<__EndList<T>>
{
    using sub_type = __EndList<T>;
    using type = type_list_wrapper<sub_type>;
};

template <>
struct  make_type_list<>
{
    using sub_type = __EmptyList;
    using type = type_list_wrapper<sub_type>;
};

template <typename ... Tp>
using type_list = typename make_type_list<Tp...>::type;


template <typename TList>
 constexpr int size() {
    return __count<typename TList::result_type>();
}

template <typename TList>
 constexpr int size(TList &&) {
    return __count<typename TList::result_type>();
}

template <typename TList, typename T>
struct  type_count
{
    enum { value =  __type_count<typename TList::result_type, T>::value };
};

template <typename TList>
struct  empty
{
    enum { value = false };
};

template <>
struct   empty<type_list_wrapper<__EmptyList>>
{
    enum { value = true };
};


template <typename TList, std::size_t N>
struct  get_type
{
    using type = typename __get_type<typename TList::result_type, N>::type;
};


template <typename TList, typename Type>
struct  has_type
{
    enum { value = __has_type<typename TList::result_type, Type>::value };
};


template <typename T, typename U, bool first = utilities::has_result_type_v<T>,
                                    bool second = utilities::has_result_type_v<U>>
struct append_impl;

template <typename T, typename U>
struct append_impl<T, U, true, true>
{
    using type = typename __append_list<typename T::result_type, typename U::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, true, false>
{
    using type = typename __append_list<typename T::result_type, typename type_list<U>::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, false, true>
{
    using type = typename __append_list<typename type_list<T>::result_type, typename U::result_type>::type;
};

template <typename T, typename U>
struct append_impl<T, U, false, false>
{
    using type = typename __append_list<typename type_list<T>::result_type, typename type_list<U>::result_type>::type;
};


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




