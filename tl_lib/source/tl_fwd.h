#pragma once

#include <cstddef>
#include <string>

namespace TL {

struct __NullType;

template <typename __T, typename __U>
struct __TypeList;

template <typename __T>
constexpr int __count_incrementer();

template <typename __TypeList>
constexpr int __count();

template <typename __TypeList, typename __T, typename __Cur = typename __TypeList::__Current, typename __Next = typename __TypeList::__Next>
struct __type_count;

template <typename TList, std::size_t N>
struct __get_type;

template <typename TList, typename Type>
struct __has_type;

template <typename TList, typename Cur = typename TList::__Current, typename Next = typename TList::__Next>
struct __empty;


} //tl
