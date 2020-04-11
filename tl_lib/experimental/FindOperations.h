#pragma once

#include "TLNulltype.hpp"
#include "TLTraits.hpp"
#include "type_list.hpp"

#include <type_traits>


namespace TL {
namespace experimental {

    template <typename TList, template <class> class Property>
    struct find_type;

    template <typename TList, template <class> class Property>
    struct find_type_impl;

    template <typename TList, template <class> class Property>
    struct find_type:   traits::is_type_list<TList>,
                        traits::has_value_variable<Property<NullType>>
    {
        using type = typename find_type_impl<TList, Property>::type;
    };

    template <typename T, typename ... Tp, template <class> class Property>
    struct find_type_impl<type_list<T, Tp...>, Property>
    {
        using type = std::conditional_t<Property<T>::value, T,
                                        typename find_type_impl<type_list<Tp...>, Property>::type>;
    };

    template <template <class> class Property>
    struct find_type_impl<type_list<>, Property>
    {
        using type = NullType;
    };

} //experimental
} //tl
