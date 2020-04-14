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
    struct all_of
    {
        inline constexpr static bool result = impl::all_of_impl<InputIt1, InputIt1, UnPred>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of
    {
        inline constexpr static bool result = impl::all_of_impl<InputIt1, InputIt1, UnPred>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of
    {
        inline constexpr static bool result = impl::all_of_impl<InputIt1, InputIt1, UnPred>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, typename T>
    struct find_type
    {
        using result = typename impl::find_type_impl<InputIt1, InputIt2, T>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_type_if
    {
        using result = typename impl::find_type_if_impl<InputIt1, InputIt2, UnPred>::result;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count
    {
        inline static constexpr bool result = impl::type_count_impl<InputIt1, InputIt2, T>::value;
    };


    /*
     * Forward declaration
     * */
    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if
    {
        inline static constexpr bool result = impl::type_count_if_impl<InputIt1, InputIt2, UnPred>::result;
    };




    /*
     * Forward declaration
     * */
    template <typename InIt1, typename InIt2, typename InIt3>
    struct equal
    {
        inline static constexpr bool result = impl::equal_impl<InIt1, InIt2, InIt3>::value;
    };



    namespace impl {

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct all_of_impl
        {
            inline constexpr static bool result = UnPred<iterator_type<InputIt1>>::result &&
                                                    all_of_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
        };

        template <typename InputIt, template <class> class UnPred>
        struct all_of_impl<InputIt, InputIt, UnPred>
        {
            inline constexpr static bool result = true;
        };

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct none_of_impl
        {
            inline constexpr static bool result = !UnPred<iterator_type<InputIt1>>::result &&
                                                    all_of_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
        };

        template <typename InputIt, template <class> class UnPred>
        struct none_of_impl<InputIt, InputIt, UnPred>
        {
            inline constexpr static bool result = true;
        };

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct any_of_impl
        {
            inline constexpr static bool result = UnPred<iterator_type<InputIt1>>::result ||
                                                    all_of_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
        };

        template <typename InputIt, template <class> class UnPred>
        struct any_of_impl<InputIt, InputIt, UnPred>
        {
            inline constexpr static bool result = true;
        };

        template <typename InputIt1, typename InputIt2, typename T>
        struct find_type_impl
        {
            template <typename Type>
            using predicate = traits::is_same<Type, T>;
            using result = typename find_type_if_impl<InputIt1, InputIt2, predicate>::result;
        };

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct find_type_if_impl
        {
            using condition = UnPred<iterator_type<InputIt1>>;
            using true_type = InputIt1;
            using false_type = typename find_type_if_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
            using result = std::conditional<condition::result, true_type, false_type>;
        };

        template <typename InputIt, template <class> class UnPred>
        struct find_type_if_impl<InputIt, InputIt, UnPred>
        {
            using result = InputIt;
        };

        template <typename InputIt1, typename InputIt2, typename T>
        struct type_count_impl
        {
            template <typename Type>
            using predicate = traits::is_same<T, Type>;
            inline static constexpr bool result = type_count_if_impl<InputIt1, InputIt2, predicate>::value;
        };

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct type_count_if_impl
        {
            inline static constexpr bool result = UnPred<iterator_type<InputIt1>>::result +
                                        type_count_if_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
        };

        template <typename InputIt, template <class> class UnPred>
        struct type_count_if_impl<InputIt, InputIt, UnPred>
        {
            inline static constexpr bool result = 0;
        };

        template <typename InIt1, typename InIt2, typename InIt3>
        struct equal_impl
        {
            using type_1 = iterator_type<InIt1>;
            using type_2 = iterator_type<InIt3>;
            inline static constexpr bool result = traits::is_same<type_1, type_2>::value &&
                                                    equal_impl<iterator_next<InIt1>, InIt2, iterator_next<InIt3>>::value;
        };

        template <typename InIt, typename InIt2>
        struct equal_impl<InIt, InIt, InIt2>
        {
            inline static constexpr bool result = true;
        };

    }

} // tl












