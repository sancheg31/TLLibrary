#pragma once

#include "TLfwd.hpp"

namespace TL {

    template <typename TIter>
    struct iterator_properties;

    template <typename TList, std::size_t I, bool = (I == 0), bool = (I == TList::length())>
    struct index_iterator;

    template <typename TList>
    struct begin;

    template <typename TList>
    struct end;

    template <typename Iter, int Distance>
    struct advance;

    template <typename Iter>
    struct next;

    template <typename Iter>
    struct prev;

    template <typename Iter1, typename Iter2>
    struct distance;

} //tl
