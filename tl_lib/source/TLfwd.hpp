#pragma once

#include <cstddef>

//TLNullType
namespace TL {
    struct NullType;
} //tl

//TLNode
namespace TL {

    template <typename T, typename U>
    struct TypeList;

} //tl

//type_list
namespace TL {

    template <typename ... Tp>
    struct type_list;

    template <typename TList>
    constexpr int size();

    template <typename ... Tp>
    constexpr int size(type_list<Tp...>&&);

    template <typename TList>
    struct length;

    template <typename TList, typename T>
    struct type_count;

    template <typename TList>
    struct empty;

    template <typename TList, std::size_t N>
    struct get_type;

    template <typename TList, typename Type>
    struct has_type;

    template <typename TList1, typename TList2>
    struct append;

} //tl


//type_list implementation
namespace TL {
namespace impl {

    template <typename TList>
    struct list_size;

    template <typename TList>
    struct list_empty;

    template <typename TList, typename Type>
    struct list_type_count;

    template <typename TList, std::size_t N>
    struct list_get_type;

    template <typename TList, typename Type>
    struct list_has_type;

    template <typename TList, typename TList2>
    struct append_list;

} //impl
} //tl


//TLTraits
namespace TL {
namespace traits {


    struct true_argument;

    struct false_argument;

    template <typename TList>
    struct is_type_list;

    template <class T>
    struct has_result_type;

    template <class T>
    struct has_value_type;

    template <class T>
    struct has_type_alias;

    template <typename T, typename U>
    struct is_same;

} //traits
} //tl

//TLUtilities
namespace TL {
namespace utilities {

    template <typename IllegalType>
    struct invalid_argument;

    template <typename ActualType, typename IllegalType>
    struct is_valid_argument;

    template <typename Type>
    struct type_or_list;

    template <std::size_t N>
    struct index_out_of_range;

} //utilities
} //tl

//TLRequirements
namespace TL {
namespace requires {

    template <typename TList>
    struct is_type_list;

    template <typename Type>
    struct is_not_nulltype;

    template <std::size_t I, std::size_t N>
    struct less_than;

} //requires
} //tl





















