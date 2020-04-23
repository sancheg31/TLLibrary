#pragma once

#include <type_traits>
#include "TLfwd.hpp"
#include "TLTypeIteratorfwd.hpp"

namespace TL {

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct all_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct any_of;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct none_of;

    template <typename InputIt1, typename InputIt2, typename T>
    struct find_type;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct find_type_if;

    template <typename InputIt1, typename InputIt2, typename T>
    struct type_count;

    template <typename InputIt1, typename InputIt2, template <class> class UnPred>
    struct type_count_if;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start,
              template <class, class> class BinPred = traits::is_same>
    struct equal;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start,
              template <class, class> class BinPred = traits::is_same>
    struct same_types;

    template <typename TList, std::size_t I, std::size_t J>
    struct swap;

    template <typename Iter1, typename Iter2>
    struct swap_iter;

    template <typename InputItStart, typename InputItEnd, typename InputIt2Start>
    struct swap_ranges;


    template <typename TIter1, typename TIter2, typename T, typename U>
    struct replace;

    template <typename TIter1, typename TIter2, template <class> class UnPred, typename U>
    struct replace_if;

    template <typename TIter1, typename TIter2>
    struct erase;

    template <typename TIter1, typename TIter2, typename T>
    struct remove;

    template <typename TIter1, typename TIter2, template <class> class UnPred>
    struct remove_if;

    template <typename TIter1, typename TIter2>
    struct reverse;

    template <typename TIterStart, typename TIterEnd, typename TIterStart2>
    struct merge;

    template <typename TIter1, typename TIter2>
    struct unique;

    namespace impl {

        template <typename TIterStart, template <class> class UnPred, std::size_t Distance>
        struct all_of_impl;

        template <typename TIterStart, template <class> class UnPred, std::size_t Distance>
        struct none_of_impl;

        template <typename TIterStart, template <class> class UnPred, std::size_t Distance>
        struct any_of_impl;

        template <typename TIterStart, typename T, std::size_t Distance>
        struct find_type_impl;

        template <typename TIterStart, template <class> class UnPred, std::size_t Distance>
        struct find_type_if_impl;

        template <typename TIterStart, typename T, std::size_t Distance>
        struct type_count_impl;

        template <typename TIterStart, template <class> class UnPred, std::size_t Distance>
        struct type_count_if_impl;

        template <typename TIterStart, typename TIterStart2, std::size_t Distance,
                  template <class, class> class BinPred>
        struct equal_impl;

        template <typename TIterStart, typename TIterEnd, typename TIterStart2,
                  template <class, class> class BinPred>
        struct same_types_impl;

        template <typename TIterStart, typename TIterEnd, typename TIterStart2, typename TIterEnd2,
                  template <class, class> class BinPred, std::size_t Length, std::size_t Offset = 0>
        struct do_same_types_impl;

        template <typename TList, std::size_t I, std::size_t J>
        struct swap_impl;

        template <typename TIter1, typename TIter2>
        struct swap_iter_impl;

        template <typename TIterStart, typename TIterStart2, std::size_t Distance>
        struct swap_ranges_impl;

        template <typename TIter1, typename TIter2, bool>
        struct reverse_impl;

        template <typename TIter, std::size_t Distance, typename T, typename U>
        struct replace_impl;

        template <typename TIter, std::size_t Distance, template <class> class UnPred, typename U>
        struct replace_if_impl;

        template <typename TIter, std::size_t Distance, typename T>
        struct remove_impl;

        template <typename TIter, std::size_t Distance, template <class> class UnPred>
        struct remove_if_impl;

        template <typename TIter, typename TNewIter, std::size_t Distance, template <class> class UnPred>
        struct do_remove_if_impl;

        template <typename TIter1, typename TIter2, std::size_t Distance>
        struct merge_impl;

        template <typename TIter, typename TIter2, typename TNewIter, std::size_t Distance>
        struct do_merge_impl;

        template <typename TIter, typename TIterEnd, std::size_t Distance = distance<TIter, TIterEnd>::result>
        struct unique_impl;

        template <typename TIter, typename TNewIter, std::size_t Distance>
        struct do_unique_impl;
    }

}


