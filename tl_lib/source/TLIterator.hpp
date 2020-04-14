#pragma once

#include <functional>
#include <iterator>

#include "TLIteratorfwd.hpp"
#include "TLRequirements.hpp"

namespace TL {

    template <typename TList, std::size_t I, std::size_t N>
    struct iterator_properties;

    template <typename TList, std::size_t I, std::size_t N>
    struct iterator_properties:
                        requires::satisfies_relation<I, N, std::less_equal>,
                        requires::satisfies_relation<I, 0, std::greater_equal>
    {
        enum { size = N };
        enum { at_start = std::equal_to<std::size_t>{}(I, 0), not_at_start = !at_start };
        enum { at_end = std::equal_to<std::size_t>{}(I, N), not_at_end = !at_end };
    };


    template <typename TList, std::size_t I, bool, bool>
    struct type_list_iterator;

    template <typename TList, std::size_t I>
    struct type_list_iterator<TList, I, false, false>:
            requires::is_type_list<TList>,
            requires::satisfies_relation<I, iterator_properties<TList, I>::size, std::less_equal>
    {
    public:
        using type = typename get_type<TList, I>::type;
        using list = TList;
        using next = type_list_iterator<TList, I+1>;
        using prev = type_list_iterator<TList, I-1>;
    };

    template <typename TList, std::size_t I>
    struct type_list_iterator<TList, I, true, false>:
            requires::is_type_list<TList>,
            requires::satisfies_relation<I, iterator_properties<TList, I>::size, std::less_equal>
    {
    public:
        using type = typename get_type<TList, I>::type;
        using list = TList;
        using next = type_list_iterator<TList, I+1>;
    };

    template <typename TList, std::size_t I>
    struct type_list_iterator<TList, I, false, true>:
            requires::is_type_list<TList>,
            requires::satisfies_relation<I, iterator_properties<TList, I>::size, std::less_equal>
    {
    public:
        using list = TList;
        using prev = type_list_iterator<TList, I-1>;
    };

    template <typename TList, std::size_t I>
    struct type_list_iterator<TList, I, true, true>:
            requires::is_type_list<TList>,
            requires::satisfies_relation<I, iterator_properties<TList, I>::size, std::less_equal>
    {
    public:
        using list = TList;
    };

    template <typename Iter>
    using iterator_type = typename Iter::type;
    template <typename Iter>
    using iterator_list = typename Iter::list;
    template <typename Iter>
    using iterator_next = typename Iter::next;
    template <typename Iter>
    using iterator_prev = typename Iter::prev;


    template <typename TList>
    struct begin
    {
        using result = type_list_iterator<TList, 0>;
    };

    template <typename TList>
    struct end
    {
        using result = type_list_iterator<TList, length<TList>::value>;
    };

    template <typename TList, std::size_t I, int Distance>
    struct advance<type_list_iterator<TList, I>, Distance>
    {
        using result = type_list_iterator<TList, I + Distance>;
    };

    template <typename TList, std::size_t I>
    struct next<type_list_iterator<TList, I>>
    {
        using result = type_list_iterator<TList, I + 1>;
    };

    template <typename TList, std::size_t I>
    struct prev<type_list_iterator<TList, I>>
    {
        using result = type_list_iterator<TList, I - 1>;
    };

    template <typename TList, std::size_t I1, std::size_t I2>
    struct distance<type_list_iterator<TList, I1>, type_list_iterator<TList, I2>>
    {
        inline constexpr static bool result = I1 - I2;
    };

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator==(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&) {
        return (I1 == I2);
    }

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator!=(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&) {
        return (I1 != I2);
    }

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator<(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&) {
        return (I1 < I2);
    }


namespace traits {

    template <typename TList1, typename TList2, std::size_t I1, std::size_t I2>
    struct is_same<TL::type_list_iterator<TList1, I1>,
                    TL::type_list_iterator<TList2, I2>>: false_argument { };

    template <typename TList, std::size_t I>
    struct is_same<type_list_iterator<TList, I>,
                    type_list_iterator<TList, I>>: true_argument { };

} //traits
} //tl

namespace std {

    template <typename TList, std::size_t I>
    struct iterator_traits<TL::type_list_iterator<TList, I>>
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
                    TL::type_list_iterator<TList2, I2>>
    {
        enum { value = (I1 == I2) && (TL::traits::is_same<TList1, TList2>::value) };
    };

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
