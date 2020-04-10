#pragma once

#include <cstddef>

#include "TLNode.h"
#include "TLNulltype.h"
#include "TLUtilities.h"

namespace TL {

    template <typename ... Tp>
    struct type_list;

}

namespace TL {
namespace traits {

    template <typename TList>
    struct is_type_list;

    template <typename ... Tp>
    struct is_type_list<type_list<Tp...>>
    {
        enum { value = true };
    };

    template <typename TList>
    struct is_type_list
    {
    private:
        enum { value = false };
    };

    template <typename TList>
    inline constexpr bool is_type_list_v = is_type_list<TList>::value;

} //traits
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
