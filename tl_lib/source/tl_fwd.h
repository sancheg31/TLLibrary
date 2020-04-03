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


template <typename ... Tp>
struct make_type_list;

template <typename T>
class type_list_wrapper;

template <typename TList>
constexpr int size();

template <typename TList>
constexpr int size(TList &&);

template <typename TList>
struct empty;

template <typename TList, typename T>
struct type_count;

template <typename TList, std::size_t N>
struct get_type;

template <typename TList, typename Type>
struct has_type;

template <typename TList1, typename TList2>
struct append;

} //tl
