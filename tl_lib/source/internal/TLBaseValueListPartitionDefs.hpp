#pragma once

#include <cstddef>
#include "TLBaseListPartitionDecls.hpp"

/**
 * list_before_index<TList, I>
 * list_after_index<TList, I>
 * list_without_index<TList, I>
 * partition_by_index<TList, I>
 */



namespace TL {
namespace internal {

    template <typename TList, std::size_t I>
    struct list_before_index;

    template <typename TList, std::size_t I>
    struct list_after_index;

    template <typename TList, std::size_t I>
    struct list_without_index;

    template <typename TList, std::size_t I>
    struct partition_by_index;



    template <typename TValueList, std::size_t I, typename TResult>
    struct do_list_before_index;

    template <template <auto...> class TValueList, auto ... Values, std::size_t I>
    struct list_before_index<TValueList<Values...>, I>
    {
        using type = typename do_list_before_index<TValueList<Values...>, I, TValueList<>>::type;
    };

    template <template <auto...> class TValueList,
              auto Value, auto ... Values, std::size_t I, auto ... RValues>
    struct do_list_before_index<TValueList<Value, Values...>, I, TValueList<RValues...>>
    {
        using type = typename do_list_before_index<TValueList<Values...>,
                                                   I,
                                                   TValueList<RValues..., Value>>::type;
    };

    template <typename TValueList, typename TResultList>
    struct do_list_before_index<TValueList, 0, TResultList>
    {
        using type = TResultList;
    };


    template <template <auto...> class TValueList, auto Value, auto ... Values, std::size_t I>
    struct list_after_index<TValueList<Value, Values...>, I>
    {
        using type = typename list_after_index<TValueList<Values...>, I - 1>::type;
    };

    template <template <auto...> class TValueList, auto Value, auto ... Values>
    struct list_after_index<TValueList<Value, Values...>, 0>
    {
        using type = TValueList<Values...>;
    };

    template <template <auto...> class TValueList>
    struct list_after_index<TValueList<>, 0>
    {
        using type = TValueList<>;
    };

    template <typename TList1, typename TList2>
    struct append_list_values;

    template <typename TValueList, std::size_t I>
    struct list_without_index
    {
        using list_before = typename list_before_index<TValueList, I>::type;
        using list_after = typename list_after_index<TValueList, I>::type;
        using type = append_list_values<list_before, list_after>;
    };


    template <class TValueList, std::size_t I>
    struct partition_by_index
    {
        using list_before_value = typename internal::list_before_index<TValueList, I>::type;
        using list_after_value = typename internal::list_after_index<TValueList, I>::type;
        using list_without_value = typename internal::list_without_index<TValueList, I>::type;
    };


} //internal
} //tl
