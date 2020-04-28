#pragma once

#include <cstddef>

/**
 * list_before_index<TList, I>
 * list_after_index<TList, I>
 * list_without_index<TList, I>
 * partition_by_index<TList, I>
 */


namespace TL {
namespace internal {

    template <typename TList, std::size_t I>
    struct list_before_index;

    template <typename TList, std::size_t I>
    using list_before_index_t = typename list_before_index<TList, I>::type;

    template <typename TList, std::size_t I>
    struct list_after_index;

    template <typename TList, std::size_t I>
    using list_after_index_t = typename list_after_index<TList, I>::type;

    template <typename TList, std::size_t I>
    struct list_without_index;

    template <typename TList, std::size_t I>
    using list_without_index_t = typename list_without_index<TList, I>::type;

    template <typename TList, std::size_t I>
    struct partition_by_index;

    template <typename TList, std::size_t I>
    using partition_by_index_t = typename partition_by_index<TList, I>::type;



} //internal
} //TL
