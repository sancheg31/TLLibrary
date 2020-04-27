#pragma once

#include "type_list.hpp"
#include "TLTraits.hpp"


namespace TL {

    template <auto Value>
    class TValue
    {
    public:
        using type = decltype(Value);
        constexpr static type value = Value;
    };

    template <typename T, typename U>
    class TypePair
    {
    public:
        using first_type = T;
        using second_type = U;
    };

    template <auto Value1, auto Value2>
    class TypePair<TValue<Value1>, TValue<Value2>>
    {
    public:
        using first_type = typename TValue<Value1>::type;
        using second_type = typename TValue<Value2>::type;

        static constexpr first_type first = Value1;
        static constexpr second_type second = Value2;

    };

    template <typename T, auto Value>
    class TypePair<T, TValue<Value>>
    {
    public:
        using first_type = T;
        using second_type = typename TValue<Value>::type;
        static constexpr second_type second = Value;
    };

    template <typename T, auto Value>
    class TypePair<TValue<Value>, T>
    {
        using first_type = typename TValue<Value>::type;
        using second_type = T;
        static constexpr first_type first = Value;
    };


} //tl
