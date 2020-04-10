#pragma once

#include <cstddef>
#include <type_traits>

#include "TLNode.hpp"
#include "TLTraits.hpp"
#include "TLRequirements.hpp"

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

    template <typename TList1, typename TList2>
    struct append;

    template <typename TList1, typename TList2>
    struct append: requires::is_type_list<TList1>
    {
    private:
        using list1 = typename utilities::type_or_list<TList1>::result;
        using list2 = typename utilities::type_or_list<TList2>::result;
    public:
        using type = type_list<typename impl::append_list<list1, list2>::type>;
    };

    template <typename TList>
    inline constexpr int length_v = length<TList>::value;

    template <typename TList>
    inline constexpr bool empty_v = empty<TList>::value;

    template <typename TList, typename Type>
    inline constexpr bool has_type_v = has_type<TList, Type>::value;

    template <typename TList, typename Type>
    inline constexpr int type_count_v = type_count<TList, Type>::value;

    template <typename TList, std::size_t N>
    using get_type_t = typename get_type<TList, N>::type;

    template <typename T, typename U>
    using append_t = typename append<T, U>::type;

} //tl


namespace TL {
namespace impl {
    /*
     * forward declaration
     * */
    template <typename TList>
    struct list_size;

    template <typename T, typename U>
    struct list_size<TypeList<T, U>>
    {
        enum { value = 1 + list_size<U>::value };
    };

    template <typename T>
    struct list_size<TypeList<T, NullType>>
    {
        enum { value = 1 };
    };

    template <>
    struct list_size<TypeList<NullType, NullType>>
    {
        enum { value = 0 };
    };

    /*
     * forward declaration
     * */
    template <typename TList>
    struct list_empty;

    template <typename T, typename U>
    struct list_empty<TypeList<T, U>>
    {
        enum { value = false };
    };

    template <>
    struct list_empty<TypeList<NullType, NullType>>
    {
        enum { value = true };
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct list_type_count;

    template <typename T, typename U, typename Type>
    struct list_type_count<TypeList<T, U>, Type>
    {
        enum { value = 0 + list_type_count<U, Type>::value };
    };

    template <typename U, typename Type>
    struct list_type_count<TypeList<Type, U>, Type>
    {
        enum { value = 1 + list_type_count<U, Type>::value };
    };

    template <typename T, typename Type>
    struct list_type_count<TypeList<T, NullType>, Type>
    {
        enum { value = 0 };
    };

    template <typename Type>
    struct list_type_count<TypeList<Type, NullType>, Type>
    {
        enum { value = 1 };
    };


    /*
     * forward declaration
     * */
    template <typename TList, std::size_t N>
    struct list_get_type;

    template <typename T, typename U, std::size_t N>
    struct list_get_type<TypeList<T, U>, N>
    {
        using type = typename list_get_type<U, N-1>::type;
    };

    template <typename T, typename U>
    struct list_get_type<TypeList<T, U>, 0>
    {
        using type = T;
    };

    template <typename T>
    struct list_get_type<TypeList<T, NullType>, 0>
    {
        using type = T;
    };

    template <typename T, std::size_t N>
    struct list_get_type<TypeList<T, NullType>, N>: utilities::index_out_of_range<N>
    {
        using type = void;
    };

    template <std::size_t N>
    struct list_get_type<TypeList<NullType, NullType>, N>: utilities::index_out_of_range<N>
    {
        using type = void;
    };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct list_has_type;

    template <typename T, typename U, typename Type>
    struct list_has_type<TypeList<T, U>, Type>
    {
        enum { value = list_has_type<U, Type>::value };
    };

    template <typename U, typename Type>
    struct list_has_type<TypeList<Type, U>, Type>
    {
        enum { value = true };
    };

    template <typename T, typename Type>
    struct list_has_type<TypeList<T, NullType>, Type>
    {
        enum { value = false };
    };

    template <typename Type>
    struct list_has_type<TypeList<Type, NullType>, Type>
    {
        enum { value = true };
    };


    template <typename TList1, typename TList2>
    struct append_list
    {
        using type = NullType;
    };

    //many to many
    template <typename Cur1, typename Next1, typename Cur2, typename Next2>
    struct append_list<TypeList<Cur1, Next1>, TypeList<Cur2, Next2>>
    {
        using type = TypeList<Cur1, typename append_list<Next1, TypeList<Cur2, Next2>>::type>;
    };

    template <typename Cur, typename Next, typename T>
    struct append_list<TypeList<Cur, Next>, T>
    {
        using type = typename append_list<TypeList<Cur, Next>, SingletonList<T>>::type;
    };

    template <typename Cur, typename Next, typename T>
    struct append_list<T, TypeList<Cur, Next>>
    {
        using type = typename append_list<SingletonList<T>, TypeList<Cur, Next>>::type;
    };

    template <typename Cur, typename Next>
    struct append_list<EmptyList, TypeList<Cur, Next>>
    {
        using type = TypeList<Cur, Next>;
    };

    template <typename Cur, typename Next>
    struct append_list<TypeList<Cur, Next>, EmptyList>
    {
        using type = TypeList<Cur, Next>;
    };

    template <>
    struct append_list<EmptyList, EmptyList>
    {
        using type = EmptyList;
    };

} //traits
} //tl




