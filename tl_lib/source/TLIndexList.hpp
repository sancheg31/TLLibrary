#pragma once

#include "TLfwd.hpp"
#include "TLTraits.hpp"
#include "TLRequirements.hpp"

namespace TL {

    template <auto ... Values>
    class IndexList;

    template <typename IndexList, std::size_t I>
    struct index_iterator;

    namespace internal {

        template <typename IndList, std::size_t N, std::size_t I = 0>
        struct DetermineValue;

        template <auto Val, auto ... Vals, std::size_t N, std::size_t I>
        struct DetermineValue<IndexList<Val, Vals...>, N, I>
        {
            constexpr static decltype(Val) value = DetermineValue<IndexList<Vals...>, N, I + 1>::value;
        };

        template <auto Val, auto ... Vals, std::size_t N>
        struct DetermineValue<IndexList<Val, Vals...>, N, N>
        {
            constexpr static decltype(Val) value = Val;
        };

        template <auto Val, auto ... Vals>
        struct DetermineType
        {
            using type = decltype(Val);
        };

        template <typename TList, std::size_t I, typename TResult = IndexList<>>
        struct list_before_index;

        template <auto ... Values, std::size_t I, typename TResult>
        struct list_before_index<IndexList<Values...>, I, TResult>
        {
        };

        template <typename TList, std::size_t I, typename TResult = IndexList<>>
        struct list_after_index;

        template <typename TList, std::size_t I, typename TResult = IndexList<>>
        struct list_without_index;

        template <typename TList, std::size_t I, std::size_t Length = TList::length()>
        struct partition_by_index;

        template <auto ... Values, std::size_t I, std::size_t Length>
        struct partition_by_index<IndexList<Values...>, I, Length>
        {
            constexpr static typename IndexList<Values...>::value_type value =
                                        IndexList<Values...>::getIndex();
            using list_before_index = typename internal::list_before_index<IndexList<Values...>, I>::type;
            using list_after_index = typename internal::list_after_index<IndexList<Values...>, I>::type
            using list_without_index = typename internal::list_without_index<IndexList<Values...>, I>::type;
        };

        template <auto ... Values, std::size_t Length>
        struct partition_by_index<IndexList<Values...>, Length, Length>
        {

        };

    }

    template <auto ... Values>
    class IndexList: requires::is_same<decltype(Values)...>
    {
    public:
        using self_type = IndexList<Values...>;
        using value_type = typename internal::DetermineType<Values...>::type;

        constexpr IndexList();
        constexpr IndexList(const self_type&);
        constexpr IndexList(self_type&&);

        constexpr self_type& operator=(const self_type&);
        constexpr self_type& operator=(self_type&&);

        constexpr static std::size_t length();

        constexpr static index_iterator<self_type, 0> begin();
        constexpr static index_iterator<self_type, internal::DetermineValue<self_type, self_type::length() - 1>::value>
        end();

        template <std::size_t Index, typename = std::enable_if_t<(sizeof...(Values) > 0)>>
        constexpr static value_type getIndex();

        constexpr static value_type first();
        constexpr static value_type last();
    };

} //tl

namespace TL {

    template <auto ... Values>
    template <std::size_t Index, typename>
    /*static*/ constexpr auto IndexList<Values...>::getIndex() -> value_type {
        return internal::DetermineValue<self_type, Index>::value;
    }

    template <auto ... Values>
    /*static*/ constexpr std::size_t IndexList<Values...>::length() {
        return sizeof...(Values);
    }

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::begin() -> index_iterator<self_type, 0> {
        return {};
    }

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::end() ->
    index_iterator<self_type, internal::DetermineValue<self_type, self_type::length() - 1>::value> {
    return {};
    }

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::first() -> value_type {
        return internal::DetermineValue<self_type, 0>::value;
    }

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::last() -> value_type {
        return internal::DetermineValue<self_type, sizeof...(Values)>::value;
    }

    template <auto ... Values>
    /*static*/ constexpr IndexList<Values...>::IndexList() = default;

    template <auto ... Values>
    /*static*/ constexpr IndexList<Values...>::IndexList(const self_type&) = default;

    template <auto ... Values>
    /*static*/ constexpr IndexList<Values...>::IndexList(self_type&&) = default;

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::operator=(const self_type&) -> self_type& = default;

    template <auto ... Values>
    /*static*/ constexpr auto IndexList<Values...>::operator=(self_type&&) -> self_type& = default;



} //tl
