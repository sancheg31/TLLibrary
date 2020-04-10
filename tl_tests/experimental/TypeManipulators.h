#pragma once


namespace TL {

    template <typename T, T N>
    struct TValue
    {
        using type = T;
        inline constexpr static type value = N;
        constexpr operator type() { return value; }
    };

    template <typename T>
    struct TType
    {
        using type = T;
    };

    template <typename T>
    struct TResult: TType<T> { };

    template <typename ... Tp>
    struct TArgs;

    template <class T>
    struct TArgs<T>
    {
        using _1 = T;
    };

    template <class T1, class T2>
    struct TArgs<T1, T2>: TArgs<T1>
    {
        using _2 = T2;
    };

    template <class T1, class T2, class T3>
    struct TArgs<T1, T2, T3>: TArgs<T1, T2>
    {
        using _3 = T3;
    };

    template <class T1, class T2, class T3, class T4>
    struct TArgs<T1, T2, T3, T4>: TArgs<T1, T2, T3>
    {
        using _4 = T4;
    };

} //tl

