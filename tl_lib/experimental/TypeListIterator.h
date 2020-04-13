#pragma once

#include "type_list.hpp"
#include "TLRequirements.hpp"
#include "TLTraits.hpp"

namespace TL {
    template <typename TList, std::size_t I = 0>
    struct type_list_iterator;

    template <typename TList, std::size_t I>
    struct type_list_iterator: requires::is_type_list<TList>
    {
    private:

        template <std::size_t N = length<TList>::value>
        struct properties:  requires::satisfies_relation<I, N, std::less_equal>,
                            requires::satisfies_relation<I, 0, std::greater_equal>
        {
            enum { value = N };
            enum { at_start = std::equal_to<std::size_t>{}(I, 0), not_at_start = !at_start };
            enum { at_end = std::equal_to<std::size_t>{}(I, N), not_at_end = !at_end };
        };
        properties<> ls{};


    public:
        using type = std::enable_if_t<properties<>::not_at_end, typename get_type<TList, I>::type>;
        using list = TList;
        using next = std::enable_if_t<properties<>::not_at_end, type_list_iterator<TList, I+1>>;
        using prev = std::enable_if_t<properties<>::not_at_start, type_list_iterator<TList, I-1>>;
    };

    template <typename ... Tp>
    type_list_iterator<type_list<Tp...>, 0> begin() {
        return type_list_iterator<type_list<Tp...>, 0>{};
    }

    template <typename ... Tp>
    type_list_iterator<type_list<Tp...>, length<type_list<Tp...>>::value> end() {
        return type_list_iterator<type_list<Tp...>, length<type_list<Tp...>>::value>{};
    }

    template <typename TList, std::size_t I, int Distance>
    constexpr TL::type_list_iterator<TList, I + Distance>
    advance(TL::type_list_iterator<TList, I> &&) {
        return TL::type_list_iterator<TList, I + Distance>{};
    }

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I + 1>
    next(TL::type_list_iterator<TList, I>&&) {
        return typename TL::type_list_iterator<TList, I>::next{};
    }

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I-1>
    prev(TL::type_list_iterator<TList, I>&&) {
        return typename TL::type_list_iterator<TList, I>::previous{};
    }

    template <typename TList, std::size_t I1, std::size_t I2>
    constexpr typename std::iterator_traits<TL::type_list_iterator<TList, I1>>::difference_type
    distance(TL::type_list_iterator<TList, I1>&&, TL::type_list_iterator<TList, I2>&&) {
        static_assert(I1 > I2, "undefined behaviour");
        return I1 - I2;
    }


namespace traits {

    template <typename TList1, typename TList2, std::size_t I1, std::size_t I2>
    struct is_same<TL::type_list_iterator<TList1, I1>,
                    TL::type_list_iterator<TList2, I2>>: false_argument { };

    template <typename TList, std::size_t I>
    struct is_same<type_list_iterator<TList, I>, type_list_iterator<TList, I>>: true_argument { };

} //traits
} //tl

namespace std {

    template <typename TList, std::size_t I>
    struct std::iterator_traits<TL::type_list_iterator<TList, I>>
    {
    private:
        using iterator = TL::type_list_iterator<TList, I>;
    public:
        using value_type = typename iterator::type;
        using difference_type = int;
        using pointer = typename iterator::type*;
        using reference = typename iterator::type&;
        using iterator_category = std::random_access_iterator_tag;
    };

    template <typename TList1, typename TList2, std::size_t I1, std::size_t I2>
    struct is_same<TL::type_list_iterator<TList1, I1>,
                    TL::type_list_iterator<TList2, I2>>:
            TL::traits::is_same<TL::type_list_iterator<TList1, I1>,
                                TL::type_list_iterator<TList2, I2>> { };

    template <typename TList, std::size_t I, class Distance>
    constexpr void
    advance(TL::type_list_iterator<TList, I>&& it, Distance d) = delete;

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I+1>
    next(TL::type_list_iterator<TList, I>&& it,
        typename std::iterator_traits<TL::type_list_iterator<TList, I>>::difference_type n) = delete;

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I-1>
    prev(TL::type_list_iterator<TList, I>&& it,
         typename std::iterator_traits<TL::type_list_iterator<TList, I>>::difference_type n) = delete;

    template <typename TList, std::size_t I1, std::size_t I2>
    constexpr typename std::iterator_traits<TL::type_list_iterator<TList, I1>>::difference_type
    distance(TL::type_list_iterator<TList, I1>&&, TL::type_list_iterator<TList, I2>&&) = delete;

} //std

