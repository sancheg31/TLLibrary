#pragma once

namespace TL {

    template <auto Value>
    class TValue
    {
    public:
        using type = decltype(Value);
        constexpr static type value = Value;
    };

    template <typename T>
    class TType
    {
    public:
        using type = T;
    };

} //tl
