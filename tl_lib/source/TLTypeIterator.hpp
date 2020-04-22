#pragma once


#include "TLTypeIteratorfwd.hpp"
#include "TLRequirements.hpp"

namespace TL {

    template <typename TList, std::size_t I>
    struct iterator_properties<type_iterator<TList, I>>:
                                                requires::in_range_inclusive<I, 0, length<TList>::value>
    {
    private:
        inline static constexpr bool at_start = (I == 0);
        inline static constexpr bool at_end = (I == length<TList>::value);
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
    struct type_iterator<TList, I, false, false>:
                                        requires::is_type_list<TList>,
                                        requires::in_range_exclusive<I, 0, length<TList>::value>
    {
    public:
        template <typename Type>
        using set_value = type_iterator<typename set_type<TList, Type, I>::type, I>;

        using value = typename get_type<TList, I>::type;
        using next = type_iterator<TList, I+1>;
        using prev = type_iterator<TList, I-1>;
    };

    template <typename TList, std::size_t I>
    struct type_iterator<TList, I, true, false>:
                                        requires::is_type_list<TList>
    {
    public:
        template <typename Type>
        using set_value = type_iterator<typename set_type<TList, Type, I>::type, I>;

        using value = typename get_type<TList, I>::type;
        using next = type_iterator<TList, I+1>;
    };

    template <typename TList, std::size_t I>
    struct type_iterator<TList, I, false, true>:
                                        requires::is_type_list<TList>
    {
    public:
        using prev = type_iterator<TList, I-1>;
    };

    template <std::size_t I>
    struct type_iterator<type_list<>, I, true, true>: requires::equal_to<I, 0> { };


    template <typename TIter>
    inline static constexpr std::size_t iterator_position = iterator_properties<TIter>::position;

    template <typename TIter, typename = std::enable_if_t<traits::is_iterator<TIter>::value>>
    using iterator_value = typename TIter::value;

    template <typename TIter>
    using iterator_list = typename iterator_properties<TIter>::list;

    template <typename TIter, typename Type, typename = std::enable_if_t<traits::is_iterator<TIter>::value>>
    using iterator_set_value = typename TIter::template set_value<Type>;

    template <typename TIter>
    using iterator_next = typename next<TIter>::result;

    template <typename TIter>
    using iterator_prev = typename prev<TIter>::result;

    template <typename TIter, std::size_t I>
    using iterator_advance = typename advance<TIter, I>::result;

    template <typename TList, typename = std::enable_if_t<traits::is_type_list<TList>::value>>
    using iterator_begin = typename begin<TList>::result;

    template <typename TList, typename = std::enable_if_t<traits::is_type_list<TList>::value>>
    using iterator_end = typename end<TList>::result;

    template <typename TIter1, typename TIter2>
    inline constexpr static bool iterator_distance = distance<TIter1, TIter2>::result;


    template <typename ... Tp>
    struct begin<type_list<Tp...>>
    {
        using result = type_iterator<type_list<Tp...>, 0>;
    };

    template <typename ... Tp>
    struct end<type_list<Tp...>>
    {
        using result = type_iterator<type_list<Tp...>, length<type_list<Tp...>>::value>;
    };

    template <typename TIter>
    struct next:
            requires::is_iterator<TIter>,
            requires::less_equal<iterator_position<TIter>, length<iterator_list<TIter>>::value>
    {
        using result = typename TIter::next;
    };

    template <typename TIter>
    struct prev:
            requires::is_iterator<TIter>,
            requires::greater_equal<iterator_position<TIter>, 0>
    {
        using result = typename TIter::prev;
    };

    template <typename TIter, int Distance>
    struct advance:
            requires::is_iterator<TIter>,
            requires::in_range_exclusive<iterator_position<TIter> + Distance, 0, length<iterator_list<TIter>>::value>
    {
        using result = std::conditional<(Distance > 0), typename advance<iterator_next<TIter>, Distance - 1>::result,
                                                        typename advance<iterator_prev<TIter>, Distance + 1>::result>;
    };

    template <typename TIter>
    struct advance<TIter, 0>
    {
        using result = TIter;
    };


    template <typename TIter1, typename TIter2>
    struct distance:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>
    {
    private:
        enum { I1 = iterator_position<TIter1>, I2 = iterator_position<TIter2> };
    public:
        inline constexpr static std::size_t result = (I1 - I2 > 0) ? (I1 - I2) : (I2 - I1);
    };




namespace traits {

    template <typename TList1, typename TList2, std::size_t I1, std::size_t I2>
    struct is_same<TL::type_iterator<TList1, I1>,
                    TL::type_iterator<TList2, I2>>: false_argument { };

    template <typename TList, std::size_t I>
    struct is_same<type_iterator<TList, I>,
                    type_iterator<TList, I>>: true_argument { };

} //traits
} //tl

namespace std {

    template <typename TList, std::size_t I>
    struct iterator_traits<TL::type_iterator<TList, I>>
    {
    private:
        using iterator = TL::type_iterator<TList, I>;
    public:
        using value_type = typename iterator::type;
        using difference_type = int;
        using pointer = typename iterator::type*;
        using reference = typename iterator::type&;
        using iterator_category = std::random_access_iterator_tag;
    };

    template <typename TList, std::size_t I, class Distance>
    constexpr void
    advance(TL::type_iterator<TList, I>&& it, Distance d) = delete;

    template <typename TList, std::size_t I>
    constexpr TL::type_iterator<TList, I+1>
    next(TL::type_iterator<TList, I>&& it,
        typename std::iterator_traits<TL::type_iterator<TList, I>>::difference_type n) = delete;

    template <typename TList, std::size_t I>
    constexpr TL::type_iterator<TList, I-1>
    prev(TL::type_iterator<TList, I>&& it,
         typename std::iterator_traits<TL::type_iterator<TList, I>>::difference_type n) = delete;

    template <typename TList, std::size_t I1, std::size_t I2>
    constexpr typename std::iterator_traits<TL::type_iterator<TList, I1>>::difference_type
    distance(TL::type_iterator<TList, I1>&&, TL::type_iterator<TList, I2>&&) = delete;

} //std
