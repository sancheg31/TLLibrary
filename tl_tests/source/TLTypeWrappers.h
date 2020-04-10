#pragma once

namespace TL {
namespace testing {

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

    template <class T, class Result>
    struct TArgs<T, Result>
    {
        using _1 = T;
        using _Result = Result;
    };

    template <class T1, class T2, class Result>
    struct TArgs<T1, T2, Result>
    {
        using _1 = T1;
        using _2 = T2;
        using _Result = Result;
    };

    template <class T1, class T2, class T3, class Result>
    struct TArgs<T1, T2, T3, Result>
    {
        using _1 = T1;
        using _2 = T2;
        using _3 = T3;
        using _Result = Result;
    };

    template <class T1, class T2, class T3, class T4, class Result>
    struct TArgs<T1, T2, T3, T4, Result>
    {
        using _1 = T1;
        using _2 = T2;
        using _3 = T3;
        using _4 = T4;
        using _Result = Result;
    };

    template <class T1, class T2, class T3, class T4, class T5, class Result>
    struct TArgs<T1, T2, T3, T4, T5, Result>
    {
        using _1 = T1;
        using _2 = T2;
        using _3 = T3;
        using _4 = T4;
        using _5 = T5;
        using _Result = Result;
    };


} //testing
} //tl
