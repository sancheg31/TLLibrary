#pragma once

#include <cstddef>
#include <type_traits>
#include <functional>

#include "TLfwd.hpp"
#include "TLIterator.hpp"
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


    template <typename TList>
     constexpr int size() {
        static_assert(traits::is_type_list<TList>::value, "type is not a type list");
        return impl::length_impl<TList>::value;
    }

    template <typename ... Tp>
     constexpr int size(type_list<Tp...> &&) {
        return impl::length_impl<type_list<Tp...>>::value;
    }


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct length;

    template <typename TList>
    struct length: requires::is_type_list<TList>
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
    template <typename TList, typename T>
    struct type_count;

    template <typename TList, typename T>
    struct type_count:  requires::is_type_list<TList>,
                        requires::is_not_nulltype<T>
    {
        enum { value =  impl::type_count_impl<TList, T>::value };
    };

    template <typename TList, typename Type>
    inline constexpr int type_count_v = type_count<TList, Type>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, std::size_t N>
    struct get_type;

    template <typename TList, std::size_t N>
    struct get_type:    requires::is_type_list<TList>,
                        requires::satisfies_relation<N, length<TList>::value, std::less>

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
                        requires::satisfies_relation<length<TList>::value, 0, std::greater>
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
                        requires::satisfies_relation<length<TList>::value, 0, std::greater>
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
                        requires::is_plain_type<Type>,
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
                            requires::is_plain_type<Type>,
                            requires::is_not_nulltype<Type>
    {
        enum { value = impl::last_type_index_impl<TList, Type>::value };
    };


    /*
     * Forward declaration
     * */
    template <typename TList, template <class> class Property>
    struct find_type;

    template <typename TList, template <class> class Property>
    struct find_type:   traits::is_type_list<TList>,
                        traits::has_value_variable<Property<NullType>>
    {
        using type = typename impl::find_type_impl<TList, Property>::type;
    };


    /*
     * Forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct all_of;

    template <typename TList, template <class> class UnPred>
    struct all_of:  requires::is_type_list<TList>,
                    requires::has_value_variable<UnPred<NullType>>
    {
        enum { value = impl::all_of_impl<typename TList::result_type, UnPred>::value };
    };

    template <typename TList, template <class> class UnPred>
    inline constexpr bool all_of_v = all_of<TList, UnPred>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct any_of;

    template <typename TList, template <class> class UnPred>
    struct any_of:  requires::is_type_list<TList>,
                    requires::has_value_variable<UnPred<NullType>>
    {
        enum { value = impl::any_of_impl<typename TList::result_type, UnPred>::value };
    };

    template <typename TList, template <class> class UnPred>
    inline constexpr bool any_of_v = any_of<TList, UnPred>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct none_of;

    template <typename TList, template <class> class UnPred>
    struct none_of: requires::is_type_list<TList>,
                    requires::has_value_variable<UnPred<NullType>>
    {
        enum { value = impl::none_of_impl<typename TList::result_type, UnPred>::value };
    };

    template <typename TList, template <class> class UnPred>
    inline constexpr bool none_of_v = none_of<TList, UnPred>::value;


    /*
     * Forward declaration
     * */
    template <typename TList1, typename TList2>
    struct equal;

    template <typename TList1, typename TList2>
    struct equal:   requires::is_type_list<TList1>,
                    requires::is_type_list<TList2>
    {
        enum { value = impl::equal_impl<TList1, TList2>::value };
    };

    template <typename TList1, typename TList2>
    struct not_equal;

    template <typename TList1, typename TList2>
    struct not_equal:   requires::is_type_list<TList1>,
                        requires::is_type_list<TList2>
    {
        enum { value = !equal<TList1, TList2>::value };
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
                        requires::is_plain_type<Type>,
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
                        requires::is_plain_type<Type>,
                        requires::is_not_nulltype<Type>
    {
        using type = typename prepend<TList, Type>::type;
    };

    template <typename T, typename U>
    using push_front_t = typename push_front<T, U>::type;

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
    template <typename TList, typename Type>
    struct type_count_impl;

    template <typename T, typename ... Tp, typename Type>
    struct type_count_impl<type_list<T, Tp...>, Type>
    {
        enum { value = type_count_impl<type_list<Tp...>, Type>::value };
    };

    template <typename ... Tp, typename Type>
    struct type_count_impl<type_list<Type, Tp...>, Type>
    {
        enum { value = 1 + type_count_impl<type_list<Tp...>, Type>::value };
    };

    template <typename Type>
    struct type_count_impl<type_list<>, Type>
    {
        enum { value = 0 };
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

    template <typename ... Tp, typename Type>
    struct has_type_impl<type_list<Tp...>, Type>
    {
        enum { value = (type_count<type_list<Tp...>, Type>::value > 0) };
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
    template <typename TList, template <class> class Property>
    struct find_type_impl;

    template <typename T, typename ... Tp, template <class> class Property>
    struct find_type_impl<type_list<T, Tp...>, Property>
    {
        using type = std::conditional_t<Property<T>::value, T,
                                        typename find_type_impl<type_list<Tp...>, Property>::type>;
    };

    template <template <class> class Property>
    struct find_type_impl<type_list<>, Property>
    {
        using type = NullType;
    };


    /*
     * forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct all_of_impl;

    template <typename T, typename U, template <class> class UnPred>
    struct all_of_impl<TypeList<T, U>, UnPred>
    {
        enum { value = UnPred<T>::value && all_of_impl<U, UnPred>::value };
    };

    template <typename T, template <class> class UnPred>
    struct all_of_impl<TypeList<T, NullType>, UnPred>
    {
        enum { value = UnPred<T>::value };
    };

    template <template <class> class UnPred>
    struct all_of_impl<TypeList<NullType, NullType>, UnPred>
    {
        enum { value = true };
    };


    /*
     * forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct any_of_impl;

    template <typename T, typename U, template <class> class UnPred>
    struct any_of_impl<TypeList<T, U>, UnPred>
    {
        enum { value = UnPred<T>::value || any_of_impl<U, UnPred>::value };
    };

    template <typename T, template <class> class UnPred>
    struct any_of_impl<TypeList<T, NullType>, UnPred>
    {
        enum { value = UnPred<T>::value };
    };

    template <template <class> class UnPred>
    struct any_of_impl<TypeList<NullType, NullType>, UnPred>
    {
        enum { value = false };
    };


    /*
     * forward declaration
     * */
    template <typename TList, template <class> class UnPred>
    struct none_of_impl;

    template <typename T, typename U, template <class> class UnPred>
    struct none_of_impl<TypeList<T, U>, UnPred>
    {
        enum { value = !UnPred<T>::value && none_of_impl<U, UnPred>::value };
    };

    template <typename T, template <class> class UnPred>
    struct none_of_impl<TypeList<T, NullType>, UnPred>
    {
        enum { value = !UnPred<T>::value };
    };

    template <template <class> class UnPred>
    struct none_of_impl<TypeList<NullType, NullType>, UnPred>
    {
        enum { value = true };
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2, std::size_t N, std::size_t I>
    struct equal_impl;

    template <typename TList1, typename TList2, std::size_t N, std::size_t I>
    struct equal_impl
    {
        enum { value = traits::is_same_v<get_type_t<TList1, I>, get_type_t<TList2, I>> && equal_impl<TList1, TList2, I + 1>::value };
    };

    template <typename TList1, typename TList2, std::size_t N>
    struct equal_impl<TList1, TList2, N, N>
    {
        enum { value = true };
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

    template <typename TList, typename T, typename ... Tp>
    struct append_types<TList, T, Tp...>
    {
        using new_type_list = typename append_type<TList, T>::type;
        using type = typename append_types<new_type_list, Tp...>::type;
    };

    template <typename TList, typename T>
    struct append_types<TList, T>
    {
        using type = typename append_type<TList, T>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct append_list;

    template <typename TList1, typename ... Tp>
    struct append_list<TList1, type_list<Tp...>>
    {
        using type = typename append_types<TList1, Tp...>::type;
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

    template <typename TList, typename T, typename ... Tp>
    struct prepend_types<TList, T, Tp...>
    {
        using new_type_list = typename prepend_types<TList, Tp...>::type;
        using type = typename prepend_type<new_type_list, T>::type;
    };

    template <typename TList, typename T>
    struct prepend_types<TList, T>
    {
        using type = typename prepend_type<TList, T>::type;
    };


    /*
     * forward declaration
     * */
    template <typename TList1, typename TList2>
    struct prepend_list;

    template <typename TList1, typename ... Tp>
    struct prepend_list<TList1, type_list<Tp...>>
    {
        using type = typename prepend_types<TList1, Tp...>::type;
    };

    template <typename TList>
    struct prepend_list<TList, type_list<>>
    {
        using type = TList;
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




} //impl
} //tl




