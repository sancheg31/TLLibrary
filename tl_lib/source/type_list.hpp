#pragma once

#include <cstddef>
#include <type_traits>

#include "TLfwd.hpp"
#include "TLNode.hpp"
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
        return impl::list_size<typename TList::result_type>::value;
    }

    template <typename ... Tp>
     constexpr int size(type_list<Tp...> &&) {
        return impl::list_size<typename type_list<Tp...>::result_type>::value;
    }


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct length;

    template <typename TList>
    struct length: requires::is_type_list<TList>
    {
        enum { value = impl::list_size<typename TList::result_type>::value }  ;
    };

    template <typename TList>
    inline constexpr int length_v = length<TList>::value;


    /*
     * Forward declaration
     * */
    template <typename TList, typename T>
    struct type_count;

    template <typename TList, typename T>
    struct type_count:  requires::is_type_list<TList>,
                        requires::is_not_nulltype<T>
    {
        enum { value =  impl::list_type_count<typename TList::result_type, T>::value };
    };

    template <typename TList, typename Type>
    inline constexpr int type_count_v = type_count<TList, Type>::value;


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct empty;

    template <typename TList>
    struct empty: requires::is_type_list<TList>
    {
        enum { value = impl::list_empty<typename TList::result_type>::value };
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
                        requires::less_than<N, length<TList>::value>
    {
        using type = typename impl::list_get_type<typename TList::result_type, N>::type;
    };

    template <typename TList, std::size_t N>
    using get_type_t = typename get_type<TList, N>::type;


    /*
     * Forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct has_type:    requires::is_type_list<TList>,
                        requires::is_not_nulltype<Type>
    {
        enum { value = impl::list_has_type<typename TList::result_type, Type>::value };
    };

    template <typename TList, typename Type>
    inline constexpr bool has_type_v = has_type<TList, Type>::value;


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
        using new_type_list = typename prepend_type<TList, T>::type;
        using type = typename prepend_types<new_type_list, Tp...>::type;
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




