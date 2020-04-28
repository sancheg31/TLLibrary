#pragma once

#include "TLBaseListPartitionDecls.hpp"


namespace TL {
namespace internal {

    template <typename TList, std::size_t I>
    struct list_before_index;

    template <typename TList, std::size_t I>
    struct list_after_index;

    template <typename TTypeList, std::size_t I>
    struct list_without_index;

    template <typename TTypeList, std::size_t I>
    struct partition_by_index;


    template <typename TTypeList, std::size_t I, typename TResult>
    struct do_list_before_index;

    template <template <typename...> class TTypeList, typename ... Types, std::size_t I>
    struct list_before_index<TTypeList<Types...>, I>
    {
        using type = typename do_list_before_index<TTypeList<Types...>, I, TTypeList<>>::type;
    };

    template <template <typename...> class TTypeList,
              typename Type, typename ... Types, std::size_t I, typename ... RTypes>
    struct do_list_before_index<TTypeList<Type, Types...>, I, TTypeList<RTypes...>>
    {
        using type = typename do_list_before_index<TTypeList<Types...>,
                                                   I,
                                                   TTypeList<RTypes..., Type>>::type;
    };

    template <typename TTypeList, typename TResultList>
    struct do_list_before_index<TTypeList, 0, TResultList>
    {
        using type = TResultList;
    };

    template <template <typename...> class TTypeList, typename Type, typename ... Types, std::size_t I>
    struct list_after_index<TTypeList<Type, Types...>, I>
    {
        using type = typename list_after_index<TTypeList<Types...>, I - 1>::type;
    };

    template <template <typename...> class TTypeList, typename Type, typename ... Types>
    struct list_after_index<TTypeList<Type, Types...>, 0>
    {
        using type = TTypeList<Types...>;
    };

    template <template <typename...> class TTypeList>
    struct list_after_index<TTypeList<>, 0>
    {
        using type = TTypeList<>;
    };

    template <typename TList1, typename TList2>
    struct append_list_types;

    template <typename TTypeList, std::size_t I>
    struct list_without_index
    {
        using list_before = typename list_before_index<TTypeList, I>::type;
        using list_after = typename list_after_index<TTypeList, I>::type;
        using type = append_list_types<list_before, list_after>;
    };


    template <class TTypeList, std::size_t I>
    struct partition_by_index
    {
        using list_before_index = typename internal::list_before_index<TTypeList, I>::type;
        using list_after_index = typename internal::list_after_index<TTypeList, I>::type;
        using list_without_index = typename internal::list_without_index<TTypeList, I>::type;
    };


} //internal
} //TL
