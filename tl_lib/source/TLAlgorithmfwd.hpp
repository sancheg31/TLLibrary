#pragma once

#include <type_traits>
#include "TLfwd.hpp"
#include "TLIteratorfwd.hpp"

namespace TL {

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of;

    template <typename InputIt1, typename InputIt2, typename T>
    struct find;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_type_if;

    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start>
    struct equal;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start>
    struct same_types;

    template <typename TList, std::size_t I, std::size_t J>
    struct swap;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start>
    struct swap_ranges;


    template <typename TList, typename T, typename U>
    struct replace;

    template <typename TList, template <class> class UnPred, typename U>
    struct replace_if;

    template <typename TList, typename T>
    struct remove;

    template <typename TList, template <class> class UnPred>
    struct remove_if;

    template <typename TList>
    struct reverse;

    template <typename TList1, typename TList2>
    struct merge;

    namespace impl {

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct all_of_impl;

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct none_of_impl;

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct any_of_impl;

        template <typename InputIt, typename InputIt2, typename T>
        struct find_type_impl;

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct find_type_if_impl;

        template <typename InputIt1, typename InputIt2, typename T>
        struct type_count_impl;

        template <typename InputIt1, typename InputIt2, template <class> class UnPred>
        struct type_count_if_impl;

        template <typename InIt1, typename InIt2, typename InIt3>
        struct equal_impl;
    }

}


