#pragma once

/**
     * append_type<TList, T>
     * append_types<TList, Tp...>
     * append_list_types<TList1, TList2>
     * prepend_type<TList, T>
     * prepend_types<TList, Tp...>
     * prepend_list_types<TList1, TList2>
 */


namespace TL {
namespace internal {

    template <typename TList, typename T>
    struct append_type;

    template <typename TList, typename ... Tp>
    struct append_types;

    template <typename TList1, typename TList2>
    struct append_list_types;

    template <template <typename...> class TTypeList, typename ... Types, typename T>
    struct append_type<TTypeList<Types...>, T>
    {
        using type = TTypeList<Types..., T>;
    };

    template <template <typename...> class TTypeList, typename ... Types, typename ... NewTypes>
    struct append_types<TTypeList<Types...>, NewTypes...>
    {
        using type = TTypeList<Types..., NewTypes...>;
    };

    template <template <typename...> class TTypeList, typename ... Types, typename ... NewTypes>
    struct append_list_types<TTypeList<Types...>, TTypeList<NewTypes...>>
    {
        using type = TTypeList<Types..., NewTypes...>;
    };


    template <typename TList, typename T>
    struct prepend_type;

    template <typename TList, typename ... Tp>
    struct prepend_types;

    template <typename TList1, typename TList2>
    struct prepend_list_types;

    template <template <typename...> class TTypeList, typename ... Types, typename T>
    struct prepend_type<TTypeList<Types...>, T>
    {
        using type = TTypeList<T, Types...>;
    };

    template <template <typename...> class TTypeList,
              typename ... Types, typename ... NewTypes>
    struct prepend_types<TTypeList<Types...>, NewTypes...>
    {
        using type = TTypeList<NewTypes..., Types...>;
    };

    template <template <typename...> class TTypeList,
              typename ... Types, typename ... NewTypes>
    struct prepend_list_types<TTypeList<Types...>, TTypeList<NewTypes...>>
    {
        using type = TTypeList<NewTypes..., Types...>;
    };





} //internal
} //tl
