#pragma once

#include "TLIndexIteratorfwd.hpp"
#include "TLfwd.hpp"
#include "TLIteratorBase.hpp"
#include "TLRequirements.hpp"

namespace TL {

    template <typename TList, std::size_t I>
    struct iterator_properties<index_iterator<TList, I>>:
            requires::in_range_inclusive<I, 0, length<TList>::value>
    {
    private:
        inline static constexpr bool at_start = (I == 0);
        inline static constexpr bool at_end = (I == TList::length());
    public:
        using list = TList;

        inline static constexpr std::size_t position = I;
        inline static constexpr bool has_list_property = true;
        inline static constexpr bool has_value_property = !at_end;
        inline static constexpr bool has_set_value_property = !at_end;
        inline static constexpr bool has_next_property = !at_end;
        inline static constexpr bool has_prev_property = !at_start;
    };

    template <typename TList, std::size_t I>
    struct index_iterator<TList, I, false, false>:
            requires::is_index_list<TList>
    {
    public:
        template <std::size_t Index>
        using set_value = index_iterator<typename set_index<TList, I, Index>::type, I>;
        inline constexpr static (typename TList::value_type) value = TList::getIndex<I>();
        using next = index_iterator<TList, I + 1>;
        using prev = index_iterator<TList, I - 1>;
    };

    template <typename TList, std::size_t I>
    struct index_iterator<TList, I, true, false>
    {
        template <std::size_t Index>
        using set_value = index_iterator<typename set_index<TList, I, Index>::type, I>;
        inline constexpr static (typename TList::value_type) value = TList::getIndex<I>();
        using next = index_iterator<TList, I + 1>;
    };

    template <typename TList, std::size_t I>
    struct index_iterator<TList, I, false, true>:
            requires::is_index_list<TList>
    {
    public:
        using prev = index_iterator<TList, I - 1>;
    };

    template <>
    struct index_iterator<IndexList<>,  0, true, true> { };



} //tl
