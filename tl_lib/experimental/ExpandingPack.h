#pragma once


#include <cstddef>


namespace TL {
namespace experimental {

template <typename ... Tp>
struct type_list { };

template <>
struct type_list<> { };

using empty_list = type_list<>;

template <typename TList, typename T>
struct append_type;

template <typename ... Tp, typename T>
struct append_type<type_list<Tp...>, T>
{
    using result = type_list<Tp..., T>;
};

template <typename T>
struct append_type<empty_list, T>
{
    using result = type_list<T>;
};

template <typename TList, typename T>
struct prepend_type;

template <typename ... Tp, typename T>
struct prepend_type<type_list<Tp...>, T>
{
    using result = type_list<T, Tp...>;
};

template <typename T>
struct prepend_type<empty_list, T>
{
    using result = type_list<T>;
};

template <typename TList, typename ... Tp>
struct append_types;

template <typename TList, typename T, typename ... Tp>
struct append_types<TList, T, Tp...>
{
    using new_type_list = typename append_type<TList, T>::result;
    using result = typename append_types<new_type_list, Tp...>::result;
};

template <typename TList, typename T>
struct append_types<TList, T>
{
    using result = typename append_type<TList, T>::result;
};

template <typename TList1, typename TList2>
struct append_list;

template <typename TList1, typename ... Tp>
struct append_list<TList1, type_list<Tp...>>
{
    using result = typename append_types<TList1, Tp...>::result;
};


template <typename TList, typename ... Tp>
struct prepend_types;


template <typename TList, typename T, typename ... Tp>
struct prepend_types<TList, T, Tp...>
{
    using new_type_list = typename prepend_type<TList, T>::type;
    using result = typename prepend_types<new_type_list, Tp...>::result;
};

template <typename TList, typename T>
struct prepend_types<TList, T>
{
    using result = typename prepend_type<TList, T>::type;
};

template <typename TList1, typename TList2>
struct prepend_list;

template <typename TList1, typename ... Tp>
struct prepend_list<TList1, type_list<Tp...>>
{
    using result = typename prepend_types<TList1, Tp...>::type;
};

template <typename TList, std::size_t, typename TResult = empty_list>
struct go_before_type;

template <typename TList, std::size_t, typename TResult = empty_list>
struct go_after_type;

template <typename T, typename ... Tp, std::size_t I, typename TResult>
struct go_before_type<type_list<T, Tp...>, I, TResult>
{
    using new_type_list = typename append_type<TResult, T>::result;
    using result = typename go_before_type<type_list<Tp...>, I-1, new_type_list>::result;
};

template <typename T, typename ... Tp, typename TResult>
struct go_before_type<type_list<T, Tp...>, 0, TResult>
{
    using result = TResult;
};


template <typename T, typename ... Tp, std::size_t I, typename TResult>
struct go_after_type<type_list<T, Tp...>, I, TResult>
{
    using result = typename go_after_type<type_list<Tp...>, I-1, TResult>::result;
};

template <typename T, typename ... Tp, typename TResult>
struct go_after_type<type_list<T, Tp...>, 0, TResult>
{
    using result = typename append_types<TResult, Tp...>::result;
};


template <typename TList, typename T, std::size_t I>
struct replace
{
    using list_before = typename go_before_type<TList, I>::result;
    using list_after = typename go_after_type<TList, I>::result;
    using list_with_type = typename append_type<list_before, T>::result;
    using result = typename append_list<list_with_type, list_after>::result;
};

template <typename TList, typename TResult = empty_list>
struct reverse;

template <typename T, typename ... Tp, typename TResult>
struct reverse<type_list<T, Tp...>, TResult>
{
    using new_type_list = typename prepend_type<TResult, T>::result;
    using result = typename reverse<type_list<Tp...>, new_type_list>::result;
};

template <typename TResult>
struct reverse<type_list<>, TResult>
{
    using result = TResult;
};


}
}












