#pragma once

#include <cstddef>

#include "tl_fwd.h"
#include "tl_utilities.h"

namespace TL {

struct __NullType
{
    __NullType() = delete;
};

namespace utilities {

template <typename T>
inline constexpr int is_NullType = std::is_same_v<T, __NullType>;

template <typename T, typename U>
inline constexpr int is_same_safe = utilities::is_same_type<T, U> && !utilities::is_NullType<T>;

} //utilities

template <typename __T, typename __U>
struct __TypeList;

template <typename __T, typename ... __U>
struct __TypeList<__T, __TypeList<__U...>>
{
    using __Current = __T;
    using __Next = __TypeList<__U...>;
};

template <typename __T>
struct __TypeList<__T, __NullType>
{
    using __Current = __T;
    using __Next = __NullType;
};

using __EmptyList = __TypeList<__NullType, __NullType>;

template <typename __T>
using __EndList = __TypeList<__T, __NullType>;



template <typename __T>
constexpr int __count_incrementer() {
    return 1;
}

template <>
constexpr int __count_incrementer<__NullType>() {
    return 0;
}

template <typename __TypeList>
constexpr int __count() {
    return __count_incrementer<typename __TypeList::__Current>() +
            __count<typename __TypeList::__Next>();
}

template <>
constexpr int __count<__NullType>() {
    return 0;
}


template <typename __T, typename __Cur, typename __Next>
struct __type_count<__TypeList<__Cur, __Next>, __T>
{
    enum { value = utilities::is_same_safe<__Cur, __T> + __type_count<__Next, __T>::value };
};

template <typename __T, typename __Cur>
struct __type_count<__EndList<__Cur>, __T>
{
    enum { value = utilities::is_same_safe<__Cur, __T> };
};

template <typename __T>
struct __type_count<__EmptyList, __T>
{
    enum { value = 0 };
};


template <typename __Cur, typename __Next, std::size_t N>
struct __get_type<__TypeList<__Cur, __Next>, N>
{
    using type = typename __get_type<__Next, N-1>::type;
};

template <typename __Cur, typename __Next>
struct __get_type<__TypeList<__Cur, __Next>, 0>
{
    using type = __Cur;
};

template <typename __Cur, std::size_t N>
struct __get_type<__EndList<__Cur>, N>
{
    //using type = __NullType;
};

template <std::size_t N>
struct __get_type<__EmptyList, N>
{
    //using type = __NullType;
};


template <typename __Cur, typename __Next, typename Type>
struct __has_type<__TypeList<__Cur, __Next>, Type>
{
    enum { value = utilities::is_same_safe<__Cur, Type> || __has_type<__Next, Type>::value  };
};

template <typename __Cur, typename Type>
struct __has_type<__EndList<__Cur>, Type>
{
    enum { value = utilities::is_same_safe<__Cur, Type> };
};

template <typename Type>
struct __has_type<__EmptyList, Type>
{
    enum { value = false };
};


template <typename TList1, typename TList2>
struct __append_list
{
    using type = __NullType;
};

//many to many
template <typename Cur1, typename Next1, typename Cur2, typename Next2>
struct __append_list<__TypeList<Cur1, Next1>, __TypeList<Cur2, Next2>>
{
    using type = __TypeList<Cur1, typename __append_list<Next1, __TypeList<Cur2, Next2>>::type>;
};

template <typename Cur, typename Next, typename T>
struct __append_list<__TypeList<Cur, Next>, T>
{
    using type = typename __append_list<__TypeList<Cur, Next>, __EndList<T>>::type;
};

template <typename Cur, typename Next, typename T>
struct __append_list<T, __TypeList<Cur, Next>>
{
    using type = typename __append_list<__EndList<T>, __TypeList<Cur, Next>>::type;
};

template <typename Cur, typename Next>
struct __append_list<__EmptyList, __TypeList<Cur, Next>>
{
    using type = __TypeList<Cur, Next>;
};

template <typename Cur, typename Next>
struct __append_list<__TypeList<Cur, Next>, __EmptyList>
{
    using type = __TypeList<Cur, Next>;
};

template <>
struct __append_list<__EmptyList, __EmptyList>
{
    using type = __EmptyList;
};


} //tl
