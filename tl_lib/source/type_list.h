#pragma once

#include <cstddef>
#include <type_traits>

#include "TLNode.h"
#include "TLTraits.h"
#include "TLRequirements.h"

namespace TL {

    template <typename ... Tp>
    struct type_list;

    template <typename T, typename ... Tp>
    struct type_list<T, Tp...>: requires::is_not_nulltype<T>
    {
        using self_type = type_list<T, Tp...>;
        using result_type = TypeList<T, typename type_list<Tp...>::result_type>;
    };

    template <typename T>
    struct type_list<T>: requires::is_not_nulltype<T>
    {
        using self_type = type_list<T>;
        using result_type = TypeList<T, NullType>;
    };

    template <>
    struct type_list<>
    {
        using self_type = type_list<>;
        using result_type = TypeList<NullType, NullType>;
    };


    template <typename TList>
     constexpr int size() {
        return impl::list_size<typename TList::result_type>::value;
    }

    template <typename ... Tp>
     constexpr int size(type_list<Tp...> &&) {
        return impl::list_size<typename type_list<Tp...>::result_type>::value;
    }

    template <typename TList>
    struct length;

    template <typename TList>
    struct length: requires::is_type_list<TList>
    {
        enum { value = impl::list_size<typename TList::result_type>::value }  ;
    };

    template <typename TList, typename T>
    struct type_count;

    template <typename TList, typename T>
    struct type_count:  requires::is_type_list<TList>,
                        requires::is_not_nulltype<T>
    {
        enum { value =  impl::list_type_count<typename TList::result_type, T>::value };
    };

    template <typename TList>
    struct empty;

    template <typename TList>
    struct empty: requires::is_type_list<TList>
    {
        enum { value = impl::list_empty<typename TList::result_type>::value };
    };

    template <typename TList, std::size_t N>
    struct get_type;

    template <typename TList, std::size_t N>
    struct get_type:    requires::is_type_list<TList>,
                        requires::less_than<N, length<TList>::value>
    {
        using type = typename impl::list_get_type<typename TList::result_type, N>::type;
    };


    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct has_type:    requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        enum { value = impl::list_has_type<typename TList::result_type, Type>::value };
    };

    template <typename T, typename U, bool first = traits::is_type_list_v<T>,
                                        bool second = traits::is_type_list_v<T>>
    struct append_impl;

    template <typename T, typename U>
    struct append_impl<T, U, true, true>
    {
        using type = typename impl::append_list<typename T::result_type, typename U::result_type>::type;
    };

    template <typename T, typename U>
    struct append_impl<T, U, true, false>
    {
        using type = typename impl::append_list<typename T::result_type, typename type_list<U>::result_type>::type;
    };

    template <typename T, typename U>
    struct append_impl<T, U, false, true>
    {
        using type = typename impl::append_list<typename type_list<T>::result_type, typename U::result_type>::type;
    };

    template <typename T, typename U>
    struct append_impl<T, U, false, false>
    {
        using type = typename impl::append_list<typename type_list<T>::result_type, typename type_list<U>::result_type>::type;
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




