#pragma once

#include <cstddef>

#include "TLNode.hpp"
#include "TLNulltype.hpp"
#include "TLUtility.hpp"

namespace TL {

    template <typename ... Tp>
    struct type_list;

}

namespace TL {
namespace traits {

    template <typename TList>
    struct is_type_list;

    template <typename ... Tp>
    struct is_type_list<type_list<Tp...>>
    {
        enum { value = true };
    };

    template <typename TList>
    struct is_type_list
    {
    private:
        enum { value = false };
    };

    template <typename TList>
    inline constexpr bool is_type_list_v = is_type_list<TList>::value;

} //traits
} //tl
