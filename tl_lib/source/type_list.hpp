#pragma once

#include <cstddef>
#include <type_traits>
#include <functional>

#include "TLfwd.hpp"
#include "TLTypeIterator.hpp"
#include "TLTraits.hpp"
#include "TLRequirements.hpp"

namespace TL {

    /*
     * Forward declaration
     * */
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


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct length;

    template <typename TList>
    struct length:
            requires::is_type_list<TList>
    {
        enum { value = impl::length_impl<TList>::value }  ;
    };

    template <typename TList>
    inline constexpr int length_v = length<TList>::value;


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct empty;

    template <typename TList>
    struct empty: requires::is_type_list<TList>
    {
        enum { value = impl::empty_impl<TList>::value };
    };

    template <typename TList>
    inline constexpr bool empty_v = empty<TList>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, std::size_t N>
    struct get_type;

    template <typename TList, std::size_t N>
    struct get_type:    requires::is_type_list<TList>,
                        requires::less<N, length<TList>::value>

    {
        using type = typename impl::get_type_impl<TList, N>::type;
    };

    template <typename TList, std::size_t N>
    using get_type_t = typename get_type<TList, N>::type;


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct first_type;

    template <typename TList>
    struct first_type:  requires::is_type_list<TList>,
                        requires::greater<length<TList>::value, 0>
    {
        using type = typename get_type<TList, 0>::type;
    };


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct last_type;

    template <typename TList>
    struct last_type:   requires::is_type_list<TList>,
                        requires::greater<length<TList>::value, 0>
    {
        using type = typename get_type<TList, length<TList>::value - 1>::type;
    };


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct has_type:    requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        enum { value = impl::has_type_impl<TList, Type>::value  };
    };

    template <typename TList, typename Type>
    inline constexpr bool has_type_v = has_type<TList, Type>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct type_index;

    template <typename TList, typename Type>
    struct type_index:  requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        enum { value =  impl::type_index_impl<TList, Type>::value };
    };


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct last_type_index;

    template <typename TList, typename Type>
    struct last_type_index: requires::is_type_list<TList>,
                            requires::is_not_nulltype<Type>
    {
        enum { value = impl::last_type_index_impl<TList, Type>::value };
    };


    /*
     * Forward declaration
     * */
    template <typename TList, std::size_t I, std::size_t J>
    struct swap:
            requires::is_type_list<TList>,
            requires::in_range_inclusive<I, 0, length<TList>::value - 1>
    {
    private:
        struct InRange: requires::in_range_inclusive<J, 0, length<TList>::value - 1> { };
    public:
        using result = typename impl::swap_impl<TList, I, J>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename TList1, typename TList2>
    struct append;

    template <typename TList1, typename TList2>
    struct append:  requires::is_type_list<TList1>,
                    requires::is_not_nulltype<TList2>
    {
        using type = typename impl::append_impl<TList1, TList2>::type;
    };

    template <typename T, typename U>
    using append_t = typename append<T, U>::type;


    /*
     * Forward declaration
     * */
    template <typename TList1, typename TList2>
    struct prepend;

    template <typename TList1, typename TList2>
    struct prepend: requires::is_type_list<TList1>,
                    requires::is_not_nulltype<TList2>
    {
        using type = typename impl::prepend_impl<TList1, TList2>::type;
    };

    template <typename T, typename U>
    using prepend_t = typename prepend<T, U>::type;


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct push_back;

    template <typename TList, typename Type>
    struct push_back:   requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        using type = typename append<TList, Type>::type;
    };

    template <typename T, typename U>
    using push_back_t = typename push_back<T, U>::type;


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct push_front;

    template <typename TList, typename Type>
    struct push_front:  requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        using type = typename prepend<TList, Type>::type;
    };

    template <typename T, typename U>
    using push_front_t = typename push_front<T, U>::type;

    /*
     * Forward declaration
     * */
    template <typename TList>
    struct pop_back;

    template <typename TList>
    struct pop_back:
            requires::is_type_list<TList>,
            requires::greater<length<TList>::value, 0>
    {
        using type = typename impl::pop_back_impl<TList>::type;
    };

    template <typename TList>
    using pop_back_t = typename pop_back<TList>::type;


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct pop_front;

    template <typename TList>
    struct pop_front:
            requires::is_type_list<TList>,
            requires::greater<length<TList>::value, 0>
    {
        using type = typename impl::pop_front_impl<TList>::type;
    };



    /*
     * Forward declaration
     * */
    template <typename TList, typename Type, std::size_t Index>
    struct set_type;

    template <typename TList, typename Type, std::size_t Index>
    struct set_type: requires::is_type_list<TList>,
                     requires::less<Index, length<TList>::value>
    {
        using type = typename impl::set_type_impl<TList, Type, Index>::type;
    };


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2>
    struct erase:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>
    {
        using type = typename impl::erase_impl<iterator_list<TIter1>,
                                                    iterator_position<TIter1>,
                                                    iterator_position<TIter2>>::type;
    };


} //tl


namespace TL {
namespace impl {

    /*
     * forward declaration
     * */
    template <typename TList>
    struct length_impl;

    template <typename ... Tp>
    struct length_impl<type_list<Tp...>>
    {
        enum { value = sizeof...(Tp) };
    };

    /*
     * forward declaration
     * */
    template <typename TList>
    struct empty_impl;

    template <typename ... Tp>
    struct empty_impl<type_list<Tp...>>
    {
        enum { value = false };
    };

    template <>
    struct empty_impl<type_list<>>
    {
        enum { value = true };
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t N, std::size_t Index>
    struct get_type_impl;

    template <typename T, typename ... Tp, std::size_t N, std::size_t Index>
    struct get_type_impl<type_list<T, Tp...>, N, Index>
    {
        using type = typename get_type_impl<type_list<Tp...>, N, Index + 1>::type;
    };

    template <typename T, typename ... Tp, std::size_t Index>
    struct get_type_impl<type_list<T, Tp...>, Index, Index>
    {
        using type = T;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type_impl;

    template <typename T, typename ... Tp, typename Type>
    struct has_type_impl<type_list<T, Tp...>, Type>
    {
        enum { value = has_type_impl<type_list<Tp...>, Type>::value };
    };

    template <typename ... Tp, typename Type>
    struct has_type_impl<type_list<Type, Tp...>, Type>
    {
        enum { value = true };
    };

    template <typename Type>
    struct has_type_impl<type_list<>, Type>
    {
        enum { value = false };
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type, std::size_t I>
    struct type_index_impl;

    template <typename T, typename ... Tp, typename Type, std::size_t I>
    struct type_index_impl<type_list<T, Tp...>, Type, I>
    {
        enum { value = type_index_impl<type_list<Tp...>, Type, I + 1>::value };
    };

    template <typename ... Tp, typename Type, std::size_t I>
    struct type_index_impl<type_list<Type, Tp...>, Type, I>
    {
        enum { value = I };
    };

    template <typename Type, std::size_t I>
    struct type_index_impl<type_list<>, Type, I>
    {
        enum { value = -1 };
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type, std::size_t I, int Position>
    struct last_type_index_impl;

    template <typename T, typename ... Tp, typename Type, int Position, std::size_t I>
    struct last_type_index_impl<type_list<T, Tp...>, Type, I, Position>
    {
        enum { value = last_type_index_impl<type_list<Tp...>, Type, I+1, Position>::value };
    };

    template <typename ... Tp, typename Type, std::size_t I, int Position>
    struct last_type_index_impl<type_list<Type, Tp...>, Type, I, Position>
    {
        enum { value = last_type_index_impl<type_list<Tp...>, Type, I+1, I>::value };
    };

    template <typename Type, std::size_t I, int Position>
    struct last_type_index_impl<type_list<>, Type, I, Position>
    {
        enum { value = Position };
    };

    /*
     * forward declaration
     * */
    template <typename TList, typename T>
    struct append_type;

    template <typename ... Tp, typename T>
    struct append_type<type_list<Tp...>, T>
    {
        using type = type_list<Tp..., T>;
    };

    template <typename T>
    struct append_type<type_list<>, T>
    {
        using type = type_list<T>;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename ... Tp>
    struct append_types;

    template <typename ...OldTypes, typename T, typename ... NewTypes>
    struct append_types<type_list<OldTypes...>, T, NewTypes...>
    {
        using new_type_list = typename append_type<type_list<OldTypes...>, T>::type;
        using type = typename append_types<new_type_list, NewTypes...>::type;
    };

    template <typename ...Types>
    struct append_types<type_list<Types...>>
    {
        using type = type_list<Types...>;
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct append_list;

    template <typename TList, typename ...NewTypes>
    struct append_list<TList, type_list<NewTypes...>>
    {
        using type = typename append_types<TList, NewTypes...>::type;
    };

    template <typename TList>
    struct append_list<TList, type_list<>>
    {
        using type = TList;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename T>
    struct prepend_type;

    template <typename ... Tp, typename T>
    struct prepend_type<type_list<Tp...>, T>
    {
        using type = type_list<T, Tp...>;
    };

    template <typename T>
    struct prepend_type<type_list<>, T>
    {
        using type = type_list<T>;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename ... Tp>
    struct prepend_types;

    template <typename ...OldTypes, typename T, typename ... NewTypes>
    struct prepend_types<type_list<OldTypes...>, T, NewTypes...>
    {
        using new_type_list = typename prepend_types<type_list<OldTypes...>, NewTypes...>::type;
        using type = typename prepend_type<new_type_list, T>::type;
    };

    template <typename ...OldTypes, typename T>
    struct prepend_types<type_list<OldTypes...>, T>
    {
        using type = typename prepend_type<type_list<OldTypes...>, T>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct prepend_list;

    template <typename TList, typename ... NewTypes>
    struct prepend_list<TList, type_list<NewTypes...>>
    {
        using type = typename prepend_types<TList, NewTypes...>::type;
    };

    template <typename TList>
    struct prepend_list<TList, type_list<>>
    {
        using type = TList;
    };

    /*
     * forward declaration
     * */
    template <typename TList, std::size_t I, std::size_t J>
    struct swap_impl
    {
        using type_1 = typename get_type<TList, I>::type;
        using type_2 = typename get_type<TList, J>::type;
        using result = typename set_type<typename set_type<TList, type_2, I>::type, type_1, J>::type;
    };

    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct append_impl;

    template <typename TList1, typename TList2>
    struct append_impl
    {
        using type = typename append_type<TList1, TList2>::type;
    };

    template <typename TList1, typename ... Tp>
    struct append_impl<TList1, type_list<Tp...>>
    {
        using type = typename append_list<TList1, type_list<Tp...>>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct prepend_impl;

    template <typename TList1, typename TList2>
    struct prepend_impl
    {
        using type = typename prepend_type<TList1, TList2>::type;
    };

    template <typename TList1, typename ... Tp>
    struct prepend_impl<TList1, type_list<Tp...>>
    {
        using type = typename prepend_list<TList1, type_list<Tp...>>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList>
    struct pop_front_impl;

    template <typename T, typename ... Tp>
    struct pop_front_impl<type_list<T, Tp...>>
    {
        using type = type_list<Tp...>;
    };


    template <typename T, typename ... Tp, typename TResult>
    struct pop_back_impl<type_list<T, Tp...>, TResult>
    {
        using new_result = typename append_type<TResult, T>::type;
        using type = typename pop_back_impl<type_list<Tp...>, new_result>::type;
    };

    template <typename T, typename TResult>
    struct pop_back_impl<type_list<T>, TResult>
    {
        using type = TResult;
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t, typename TResult>
    struct list_before_index;

    template <typename T, typename ... Tp, std::size_t I, typename TResult>
    struct list_before_index<type_list<T, Tp...>, I, TResult>
    {
        using new_type_list = typename append_type<TResult, T>::type;
        using type = typename list_before_index<type_list<Tp...>, I - 1, new_type_list>::type;
    };

    template <typename T, typename ... Tp, typename TResult>
    struct list_before_index<type_list<T, Tp...>, 0, TResult>
    {
        using type = TResult;
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t, typename TResult>
    struct list_after_index;

    template <typename T, typename ... Tp, std::size_t I, typename TResult>
    struct list_after_index<type_list<T, Tp...>, I, TResult>
    {
        using type = typename list_after_index<type_list<Tp...>, I-1, TResult>::type;
    };

    template <typename T, typename ... Tp, typename TResult>
    struct list_after_index<type_list<T, Tp...>, 0, TResult>
    {
        using type = typename append_types<type_list<>, Tp...>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t I, typename TResult>
    struct list_without_index;

    template <typename ... Tp, std::size_t I, typename TResult>
    struct list_without_index<type_list<Tp...>, I, TResult>
    {
        using new_type_list = typename list_before_index<type_list<Tp...>, I, TResult>::type;
        using type = typename list_after_index<type_list<Tp...>, I, new_type_list>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t I, std::size_t Length>
    struct partition_by_index
    {
        using type = typename get_type<TList, I>::type;
        using list_before_index = typename TL::impl::list_before_index<TList, I>::type;
        using list_after_index = typename TL::impl::list_after_index<TList, I>::type;
        using list_without_index = typename TL::impl::list_without_index<TList, I>::type;
    };

    template <typename TList, std::size_t Length>
    struct partition_by_index<TList, Length, Length>
    {
        using list_before_index = TList;
        using list_after_index = type_list<>;
        using list_without_index = TList;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type, std::size_t Index>
    struct set_type_impl;

    template <typename TList, typename Type, std::size_t Index>
    struct set_type_impl
    {
        using partition = partition_by_index<TList, Index>;
        using list_with_type = typename append_type<typename partition::list_before_index,
                                                    Type>::type;
        using type = typename append_list<list_with_type,
                                          typename partition::list_after_index>::type;
    };

    /*
     * forward declaration
     * */
    template <typename TList, std::size_t I, std::size_t J>
    struct erase_impl
    {
        using index_i = partition_by_index<TList, I>;
        using index_j = partition_by_index<TList, J>;
        using before = typename index_i::list_before_index;
        using after = typename index_j::list_after_index;
        using list_with_end_type = typename append_type_if_not_at_end<TList, before, J, length<TList>::value>::type;
        using type = typename append_list<list_with_end_type, after>::type;
    };

    template <typename TList, std::size_t Index>
    struct erase_impl<TList, Index, Index>
    {
        using type = TList;
    };

    template <typename TSourceList, typename TDestList, std::size_t I, std::size_t Length>
    struct append_type_if_not_at_end
    {
        using type = typename append_type<TDestList, typename get_type<TSourceList, I>::type>::type;
    };

    template <typename TSourceList, typename TDestList, std::size_t Length>
    struct append_type_if_not_at_end<TSourceList, TDestList, Length, Length>
    {
        using type = TDestList;
    };

} //impl
} //tl




