#pragma once
#include "tuple.hpp"
#include <type_traits>

namespace cpputils
{
    template <typename FP, class C, class Tuple, std::enable_if_t<!std::is_pointer_v<C>, bool> = true, std::size_t... I>
    constexpr decltype(auto) apply_memfun_imp(FP f, C obj, Tuple t, std::index_sequence<I...>)
    {
        return (obj.*f)(std::get<I>(t)...);
    }

    template <typename FP, class C, class Tuple, std::enable_if_t<std::is_pointer_v<C>, bool> = true, std::size_t... I>
    constexpr decltype(auto) apply_memfun_imp(FP f, C obj, Tuple t, std::index_sequence<I...>)
    {
        return (obj->*f)(std::get<I>(t)...);
    }

    template<typename F, class Tuple, std::enable_if_t<std::is_member_pointer_v<std::decay_t<F>>, bool> = true, std::size_t... I>
    constexpr decltype(auto) apply_imp(F f, Tuple t, std::index_sequence<I...>)
    {
        return apply_memfun_imp(f, std::get<0>(t), sub_tuple<1, std::tuple_size<decltype(t)>::value - 1>(t), std::make_index_sequence<std::tuple_size<decltype(t)>::value - 1>());
    }

    template<typename F, class Tuple, std::enable_if_t<!std::is_member_pointer_v<std::decay_t<F>>, bool> = true, std::size_t... I>
    constexpr decltype(auto) apply_imp(F f, Tuple t, std::index_sequence<I...>)
    {
        return f(std::get<I>(t)...);
    }

    template<typename F, class Tuple>
    constexpr decltype(auto) apply(F f, Tuple t)
    {
        return apply_imp(f, t, std::make_index_sequence<std::tuple_size<Tuple>::value>());
    }
}