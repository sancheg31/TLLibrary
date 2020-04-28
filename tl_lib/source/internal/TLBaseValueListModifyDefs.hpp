#pragma once


/**
     * append_value<TList, T>
     * append_values<TList, Tp...>
     * append_list_values<TList1, TList2>
     * prepend_value<TList, T>
     * prepend_values<TList, Tp...>
     * prepend_list_values<TList1, TList2>
 */

namespace TL {
namespace internal {

    template <typename TValueList, auto Value>
    struct append_value;

    template <typename TList, auto ... Values>
    struct append_values;

    template <typename TList1, typename TList2>
    struct append_list_values;

    template <template <auto...> class TValueList,
                auto ... Values, auto Value>
    struct append_value<TValueList<Values...>, Value>
    {
        using type = TValueList<Values..., Value>;
    };

    template <template <auto...> class TValueList,
                auto ... Values, auto ... NewValues>
    struct append_values<TValueList<Values...>, NewValues...>
    {
        using type = TValueList<Values..., NewValues...>;
    };

    template <template <auto...> class TValueList, auto ... Values, auto ... NewValues>
    struct append_list_values<TValueList<Values...>, TValueList<NewValues...>>
    {
        using type = TValueList<Values..., NewValues...>;
    };


    template <typename TValueList, auto Value>
    struct prepend_value;

    template <typename TList, auto ... Values>
    struct prepend_values;

    template <typename TList1, typename TList2>
    struct prepend_list_values;

    template <template <auto...> class TValueList,
                auto ... Values, auto Value>
    struct prepend_value<TValueList<Values...>, Value>
    {
        using type = TValueList<Value, Values...>;
    };

    template <template <auto...> class TValueList,
                auto ... Values, auto ... NewValues>
    struct prepend_values<TValueList<Values...>, NewValues...>
    {
        using type = TValueList<NewValues..., Values...>;
    };

    template <template <auto...> class TValueList, auto ... Values, auto ... NewValues>
    struct prepend_list_values<TValueList<Values...>, TValueList<NewValues...>>
    {
        using type = TValueList<NewValues..., Values...>;
    };


} //internal
} //TL
