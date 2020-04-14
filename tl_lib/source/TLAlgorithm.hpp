#pragma once

#include "TLAlgorithmfwd.hpp"
#include "TLIterator.hpp"
#include "TLTraits.hpp"

#include <type_traits>

namespace TL {

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of_impl;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of
    {
        inline constexpr static bool result = all_of_impl<InputIt1, InputIt1, UnPred>::result;
    };

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
    struct none_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of_impl;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of
    {
        inline constexpr static bool result = all_of_impl<InputIt1, InputIt1, UnPred>::result;
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
    struct any_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred,
              bool = traits::is_same<iterator_next<InputIt1>, InputIt2>::result>
    struct any_of_impl;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of
    {
        inline constexpr static bool result = all_of_impl<InputIt1, InputIt1, UnPred>::result;
    };


    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of_impl<InputIt1, InputIt2, UnPred, false>
    {
        inline constexpr static bool result = UnPred<iterator_type<InputIt1>>::result ||
                                                all_of_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
    };

    template <typename InputIt, template <class> class UnPred>
    struct any_of_impl<InputIt, InputIt, UnPred, true>
    {
        inline constexpr static bool result = true;
    };


    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_if;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_if_impl;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_if
    {
        using result = typename find_if_impl<InputIt1, InputIt2, UnPred>::result;
    };

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_if_impl
    {
        using condition = UnPred<iterator_type<InputIt1>>;
        using true_type = InputIt1;
        using false_type = typename find_if_impl<iterator_next<InputIt1>, InputIt2, UnPred>::result;
        using result = std::conditional<condition::result, true_type, false_type>;
    };

    template <typename InputIt, template <class> class UnPred>
    struct find_if_impl<InputIt, InputIt, UnPred>
    {
        using result = InputIt;
    };

    template <typename InputIt1, typename InputIt2, typename T>
    struct find;

    template <typename InputIt, typename InputIt2, typename T>
    struct find_impl;

    template <typename InputIt1, typename InputIt2, typename T>
    struct find
    {
        using result = typename find_impl<InputIt1, InputIt2, T>::result;
    };

    template <typename InputIt1, typename InputIt2, typename T>
    struct find_impl
    {
        template <typename Type>
        using predicate = traits::is_same<Type, T>;
        using result = typename find_if_impl<InputIt1, InputIt2, predicate>::result;
    };


    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if_impl;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if
    {
        inline static constexpr bool result = type_count_if_impl<InputIt1, InputIt2, UnPred>::result;
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


    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count;

    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count_impl;


    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count
    {
        inline static constexpr bool result = type_count_impl<InputIt1, InputIt2, T>::value;
    };

    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count_impl
    {
        template <typename Type>
        using predicate = traits::is_same<T, Type>;
        inline static constexpr bool result = type_count_if_impl<InputIt1, InputIt2, predicate>::value;
    };







} // tl












