#pragma once

#include "TLAlgorithmfwd.hpp"
#include "TLIterator.hpp"
#include "TLTraits.hpp"

#include <type_traits>

namespace TL {

    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        inline constexpr static bool result = impl::all_of_impl<InputIt1, UnPred,
                                                                distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        inline constexpr static bool result = impl::none_of_impl<InputIt1, UnPred,
                                                                distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        inline constexpr static bool result = impl::any_of_impl<InputIt1, UnPred,
                                                                distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, typename T>
    struct find_type:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>
    {
        using result = typename impl::find_type_impl<InputIt1, T,
                                                    distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_type_if:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        using result = typename impl::find_type_if_impl<InputIt1, UnPred, distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>
    {
        inline static constexpr bool result = impl::type_count_impl<InputIt1, T, distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if:
            requires::is_iterator<InputIt1, InputIt2>,
            requires::is_same<iterator_list<InputIt1>, iterator_list<InputIt2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        inline static constexpr bool result = impl::type_count_if_impl<InputIt1, UnPred,
                                                                        distance<InputIt1, InputIt2>::result>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InIt1, typename InIt2, typename InIt3>
    struct equal:
            requires::is_iterator<InIt1, InIt2, InIt3>,
            requires::is_same<iterator_list<InIt1>, iterator_list<InIt2>>
    {
        inline static constexpr bool result = impl::equal_impl<InIt1, InIt3, distance<InIt1, InIt2>::result>::value;
    };


    /*
     * Forward declaration
     * */
    template <typename TList, std::size_t I, std::size_t J>
    struct swap:
            requires::is_type_list<TList>,
            requires::in_range_inclusive<I, 0, length<TList>::value - 1>,
            requires::in_range_inclusive<J, 0, length<TList>::value - 1>
    {
        using result = typename impl::swap_impl<TList, I, J>::result;
    };

    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2>
    struct swap_iter:
            requires::is_iterator<TIter1, TIter2>
    {
        using result = typename impl::swap_iter_impl<TIter1, TIter2>::result;
    };

    /*
     * Forward declaration
     * */
    template <typename TIterStart, typename TIterEnd, typename TIterStart2>
    struct swap_ranges:
                requires::is_iterator<TIterStart, TIterEnd, TIterStart2>,
                requires::is_same<iterator_list<TIterStart>, iterator_list<TIterEnd>>
    {
        using result = typename impl::swap_ranges_impl<TIterStart, TIterStart2,
                                                        distance<TIterStart, TIterEnd>::result>::result;
    };


    /*
     * Forward declaration
     * */
    namespace impl {
        template <typename TIter1, typename TIter2, bool = std::less<std::size_t>{}(iterator_position<TIter1>,
                                                                                    iterator_position<TIter2>)>
        struct reverse_impl;
    }


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2>
    struct reverse:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>
    {
        using result = typename impl::reverse_impl<TIter1, TIter2>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2, typename T, typename U>
    struct replace:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>
    {
        using result = typename impl::replace_impl<TIter1, distance<TIter1, TIter2>::result, T, U>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2, template <class> class UnPred, typename U>
    struct replace_if:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        using result = typename impl::replace_if_impl<TIter1, distance<TIter1, TIter2>::result, UnPred, U>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2, typename T>
    struct remove:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>
    {
        using result = typename impl::remove_impl<TIter1, distance<TIter1, TIter2>::result, T>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename TIter1, typename TIter2, template <class> class UnPred>
    struct remove_if:
            requires::is_iterator<TIter1, TIter2>,
            requires::is_same<iterator_list<TIter1>, iterator_list<TIter2>>,
            requires::has_value_variable<UnPred<NullType>>
    {
        using result = typename impl::remove_if_impl<TIter1, distance<TIter1, TIter2>::result, UnPred>::result;
    };


    namespace impl {

        template <typename TIterStart, template <class> class UnPred, int Distance>
        struct all_of_impl
        {
            inline constexpr static bool result = UnPred<iterator_type<TIterStart>>::value &&
                                                    all_of_impl<iterator_next<TIterStart>, UnPred, Distance - 1>::result;
        };

        template <typename TIterStart, template <class> class UnPred>
        struct all_of_impl<TIterStart, UnPred, 0>
        {
            inline constexpr static bool result = true;
        };

        template <typename TIterStart, template <class> class UnPred, int Distance>
        struct none_of_impl
        {
            inline constexpr static bool result = !UnPred<iterator_type<TIterStart>>::value &&
                                                    none_of_impl<iterator_next<TIterStart>, UnPred, Distance - 1>::result;
        };

        template <typename TIterStart, template <class> class UnPred>
        struct none_of_impl<TIterStart, UnPred, 0>
        {
            inline constexpr static bool result = true;
        };

        template <typename TIterStart, template <class> class UnPred, int Distance>
        struct any_of_impl
        {
            inline constexpr static bool result = UnPred<iterator_type<TIterStart>>::value ||
                                                    any_of_impl<iterator_next<TIterStart>, UnPred, Distance - 1>::result;
        };

        template <typename TIterStart, template <class> class UnPred>
        struct any_of_impl<TIterStart, UnPred, 0>
        {
            inline constexpr static bool result = true;
        };

        template <typename TIterStart, typename T, int Distance>
        struct find_type_impl
        {
            template <typename Type>
            using predicate = traits::is_same<Type, T>;
            using result = typename find_type_if_impl<TIterStart, predicate, Distance>::result;
        };

        template <typename TIterStart, template <class> class UnPred, int Distance>
        struct find_type_if_impl
        {
            using condition = UnPred<iterator_type<TIterStart>>;
            using true_type = TIterStart;
            using false_type = typename find_type_if_impl<iterator_next<TIterStart>, UnPred, Distance - 1>::result;
            using result = std::conditional<condition::value, true_type, false_type>;
        };

        template <typename TIterStart, template <class> class UnPred>
        struct find_type_if_impl<TIterStart, UnPred, 0>
        {
            using result = TIterStart;
        };

        template <typename TIterStart, typename T, int Distance>
        struct type_count_impl
        {
            template <typename Type>
            using predicate = traits::is_same<T, Type>;
            inline static constexpr bool result = type_count_if_impl<TIterStart, predicate, Distance>::result;
        };


        template <typename TIterStart, template <class> class UnPred, int Distance>
        struct type_count_if_impl
        {
            inline static constexpr bool result = UnPred<iterator_type<TIterStart>>::value +
                                        type_count_if_impl<iterator_next<TIterStart>, UnPred, Distance - 1>::result;
        };

        template <typename TIterStart, template <class> class UnPred>
        struct type_count_if_impl<TIterStart, UnPred, 0>
        {
            inline static constexpr bool result = 0;
        };


        template <typename InIt1, typename InIt2, int Distance>
        struct equal_impl
        {
            using type_1 = iterator_type<InIt1>;
            using type_2 = iterator_type<InIt2>;
            inline static constexpr bool result = traits::is_same<type_1, type_2>::value &&
                                                    equal_impl<iterator_next<InIt1>, iterator_next<InIt2>, Distance - 1>::result;
        };

        template <typename InIt1, typename InIt2>
        struct equal_impl<InIt1, InIt2, 0>
        {
            inline static constexpr bool result = true;
        };


        template <typename TList, std::size_t I, std::size_t J>
        struct swap_impl
        {
            using type_1 = typename get_type<TList, I>::type;
            using type_2 = typename get_type<TList, J>::type;
            using result = typename set_type<typename set_type<TList, type_2, I>::type, type_1, J>::type;
        };


        //add implementation with type pair
        template <typename TIter1, typename TIter2>
        struct swap_iter_impl
        {
            using type_1 = iterator_type<TIter1>;
            using type_2 = iterator_type<TIter2>;
            using result = type_list<iterator_set<TIter1, type_1>, iterator_set<TIter2, type_2>>;
        };


        template <typename TIterStart, typename TIterStart2, int Distance>
        struct swap_ranges_impl
        {
            using new_iter = typename swap_iter<TIterStart, TIterStart2>::result;
            using new_iter_1 = typename get_type<new_iter, 0>::type;
            using new_iter_2 = typename get_type<new_iter, 1>::type;
            using result = typename swap_ranges_impl<iterator_next<new_iter_1>, iterator_next<new_iter_2>, Distance - 1>::result;
        };

        template <typename TIterStart, typename TIterStart2>
        struct swap_ranges_impl<TIterStart, TIterStart2, 0>
        {
            using result = TIterStart2;
        };


        template <typename TIter1, typename TIter2>
        struct reverse_impl<TIter1, TIter2, true>
        {
            using new_iters = typename swap_iter_impl<TIter1, TIter2>::result;
            using new_iter_1 = typename get_type<new_iters, 0>::type;
            using new_iter_2 = typename get_type<new_iters, 1>::type;
            using result = typename reverse_impl<iterator_next<new_iter_1>, iterator_prev<new_iter_2>>::result;
        };

        template <typename TIter1, typename TIter2>
        struct reverse_impl<TIter1, TIter2, false>
        {
            using result = TIter2;
        };


        template <typename TIter, std::size_t Distance, template <class> class UnPred, typename U>
        struct replace_if_impl
        {
            using condition = UnPred<iterator_type<TIter>>;
            using new_iter = std::conditional_t<condition::value, iterator_set<TIter, U>, TIter>;
            using result = typename replace_if_impl<iterator_next<new_iter>, Distance - 1, UnPred, U>::result;
        };

        template <typename TIter, template <class> class UnPred, typename U>
        struct replace_if_impl<TIter, 0, UnPred, U>
        {
            using result = TIter;
        };

        template <typename TIter, std::size_t Distance, typename T, typename U>
        struct replace_impl
        {
            template <typename Type>
            using condition = traits::is_same<T, Type>;
            using result = typename replace_if_impl<TIter, Distance, condition, U>::result;
        };

        template <typename TIter, std::size_t Distance, typename T>
        struct remove_impl
        {
            template <typename Type>
            using condition = traits::is_same<Type, T>;
            using result = typename remove_if_impl<TIter, Distance, condition>::result;
        };

        template <typename TIter, std::size_t Distance, template <class> class UnPred>
        struct remove_if_impl
        {
            using result_iter = typename find_type_if_impl<TIter, UnPred, Distance>::result;
            inline static constexpr std::size_t diff = iterator_distance<TIter, result_iter>;
            using result = typename do_remove_if_impl<iterator_next<result_iter>, result_iter, Distance - diff, UnPred>::result;
        };

        template <typename TIter, typename TNewIter, std::size_t Distance, template <class> class UnPred>
        struct do_remove_if_impl
        {
            using type = iterator_type<TIter>;
            using condition = UnPred<type>;
            using new_iter = std::conditional_t<condition::value, iterator_next<iterator_set<TNewIter, type>>,
                                                                    TNewIter>;
            using result = typename do_remove_if_impl<iterator_next<TIter>, new_iter, Distance - 1, UnPred>::result;
        };

    } //impl

} // tl












