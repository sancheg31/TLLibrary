#pragma once

#include <gtest/gtest.h>

#include "source/TLfwd.hpp"

namespace TL {
namespace testing {

class TLTestBase {

protected:


    template <typename T, typename U>
    static constexpr bool is_same_v = std::is_same<T, U>::value;

    using empty_list = TL::type_list<>;
    constexpr static std::size_t empty_list_size = 0;

    using singleton_list = TL::type_list<int>;
    using singleton_0 = int;

    constexpr static std::size_t singleton_list_size = 1;

    using integrals = TL::type_list<char, short, int, long>;
    using integrals_0 = char;
    using integrals_1 = short;
    using integrals_2 = int;
    using integrals_3 = long;
    constexpr static std::size_t integrals_size = 4;

    using doubles = TL::type_list<float, double>;
    using doubles_0 = float;
    using doubles_1 = double;
    constexpr static std::size_t doubles_size = 2;

    struct Inner1 { }; struct Inner2 { }; struct Inner3 { };
    using list_1_2_3 = type_list<Inner1, Inner2, Inner3>;
    using list_1_1_1 = type_list<Inner1, Inner1, Inner1>;
    using list_2_1_2 = type_list<Inner2, Inner1, Inner2>;
    using list_3_2_3 = type_list<Inner3, Inner2, Inner3>;
    using list_1_1 = type_list<Inner1, Inner1>;
    using list_2_1 = type_list<Inner2, Inner1>;
    using list_3_2 = type_list<Inner3, Inner2>;
    using list_1_2 = type_list<Inner1, Inner2>;
    using list_2_3 = type_list<Inner2, Inner3>;
    using list_1 = type_list<Inner1>;
    using list_2 = type_list<Inner2>;
    using list_3 = type_list<Inner3>;

};


} //testing
} //tl
